// DecoderHelpers.cpp

#include <stdint.h>
#include <cpu/DecoderHelpers.h>
#include <cpu/RegisterFile.h>
#include <misc/miscHelpers.h>
#include <stdexcept>

#define ZEROPAGE_OFFSET 0x0000

class DecoderHelpers : BinaryHelpers {
    // Memory and page cross checking
protected:
    bool CheckPageCrossOffset(uint16_t baseAddress, uint8_t addressOffset){
        // Checks if address spills onto next page, eg next 256byte chunk
        uint16_t nextAddress;
        uint8_t pageIdCurrent, pageIdNext;

        // compute next jump
        nextAddress = baseAddress + addressOffset;
        // determine page block IDs
        pageIdCurrent = (baseAddress & 0xFF00) >> 8; // keep upper byte and truncate to section
        pageIdNext = (nextAddress & 0xFF00) >> 8; // keep upper byte and truncate to section

        // if page IDs are the same, their difference will be 0
        return pageIdCurrent == pageIdNext;
    };

    uint8_t ComputeTotalRuntimePageCross(uint16_t baseAddress, uint8_t addressOffset, uint8_t baseCycleCost, uint8_t pageCrossExtraCycles){
        // YES/NO: did we cross page?
        bool crossedPage = CheckPageCrossOffset(baseAddress, addressOffset);
        uint8_t instructionCycleCost;
        if (!crossedPage) instructionCycleCost = baseCycleCost + pageCrossExtraCycles;
        else instructionCycleCost = baseCycleCost;
        return instructionCycleCost;
    };

    bool checkIfDataZero(uint8_t data){return data == 0x00;}
    bool checkIfDataNegative(uint8_t data){return ((data & 0x80) == 0x80);}; // data AND 0b1000.0000 is only equal to 0b1000.0000 IF data MSB is 1, otherwise is equal to 0
    bool checkIfOperationOverflow(uint8_t operandA, uint8_t operandB, bool carryBit = 0 ) {
        uint16_t resultRaw = static_cast<uint16_t>(operandA) + static_cast<uint16_t>(operandB) + static_cast<uint16_t>(carryBit);
        // NOTE: Overflow occurs when result is outside of bounds (-127,+128). Overflow is meant for signed representations of numbers.
        // We can check  overflow by comparing the signs of the results and operands
        uint8_t resultTruncated = static_cast<uint8_t>(resultRaw);
        int8_t signedA = static_cast<int8_t>(operandA);
        int8_t signedB = static_cast<int8_t>(operandB);
        int8_t signedResult = static_cast<int8_t>(resultTruncated);
        // Essentially:
        // - A and B same sign -> check overflow
        // - A and B different signs -> never check overflow
        // In case 1, overflow occurs if sign of A (or B) differs from the result sign
        bool overflow =
            ((signedA >= 0 && signedB >= 0 && signedResult < 0) ||
            (signedA < 0 && signedB < 0 && signedResult >= 0));
        return overflow;
    };
    bool checkIfOperationCarry(uint8_t operandA, uint8_t operandB, bool carryBit = 0) {
        uint16_t resultRaw = static_cast<uint16_t>(operandA) + static_cast<uint16_t>(operandB) + static_cast<uint16_t>(carryBit);
        // Easiest: check if truncated lower 8 bits matches full 16bit. If overflow, they will diverge
        uint16_t resultTruncated = resultRaw | 0x00FF;
        return resultRaw == resultTruncated;
    };
    OperandData fetchOperands(const Instruction& instr, uint16_t baseAddress, Memory& ram, RegisterFile& RF, ChipType processorFamily = ChipType::NMOS6502){
        uint8_t byteCount = instr.byteCount; 
        AddressingMode instrAddressingMode = instr.addressMode;
        std::vector<uint8_t> instrBuffer = ram.fetchBytes(baseAddress, byteCount); //fetch buffer of opcode + operands
        bool hasPageCrossedInstruction = ram.getPageIDFromAddress(baseAddress) == ram.getPageIDFromAddress(baseAddress + (byteCount - 1)); // page has been crossed for the instruction IF they differ between top and bottom bytes
        // init and start construction of operand package
        OperandData operands;
        // pack existing information
        operands.resolvedAddressingMode = instrAddressingMode;
        operands.insructionPageCrossed = hasPageCrossedInstruction;
        
        switch (instrAddressingMode)
        {
        case AddressingMode::Implied:
            // operands A and B are assumed null, this is a default
            break;
        
        case AddressingMode::Immediate:
            // Immediate instructions are always 2 bytes
            operands.operandA = instrBuffer[1]; // 6502 uses LE convention but buffer is flipped: operand is at index 0
            break;
        case AddressingMode::Absolute:
            // Absolute addresses are ALWAYS 3 bytes, with data field here encoding the address at which data is fetched
            uint16_t resolvedAddress = concatenateWordFromTwoBytes(instrBuffer[2], instrBuffer[1]); // this is the address of our operand
            operands.operandA = ram.readByte(resolvedAddress); // get byte from address
            break;

        case AddressingMode::ZeroPage:
            // These instructions are always two-byte (operand + lower ZP address byte
            uint16_t resolvedAddress = static_cast<uint16_t>(ZEROPAGE_OFFSET) & static_cast<uint16_t>(instrBuffer[1]);   
            operands.operandA = ram.readByte(resolvedAddress); // get byte from address
            break;
        
        case AddressingMode::AbsoluteXIndexed:
            uint16_t resolvedAddressBase = concatenateWordFromTwoBytes(instrBuffer[2], instrBuffer[1]); // this is the address of our operand
            uint16_t resolvedAddress = resolvedAddressBase + static_cast<uint16_t>(RF.X.read()); // This mode does operand address (like absolute mode) + X
            uint8_t basePageID = ram.getPageIDFromAddress(resolvedAddressBase);
            uint8_t resolvedPageID = ram.getPageIDFromAddress(resolvedAddress);
            operands.operandA = ram.readByte(resolvedAddress); // get byte from address
            operands.operandPageCrossed == static_cast<bool>(basePageID != resolvedPageID); //instruction takes an additional cycle if adding X changes the page
            break;
                
        case AddressingMode::AbsoluteYIndexed:
            uint16_t resolvedAddressBase = concatenateWordFromTwoBytes(instrBuffer[2], instrBuffer[1]); // this is the address of our operand
            uint16_t resolvedAddress = resolvedAddressBase + static_cast<uint16_t>(RF.Y.read()); // This mode does operand address (like absolute mode) + X
            uint8_t basePageID = ram.getPageIDFromAddress(resolvedAddressBase);
            uint8_t resolvedPageID = ram.getPageIDFromAddress(resolvedAddress);
            operands.operandA = ram.readByte(resolvedAddress); // get byte from address
            operands.operandPageCrossed == static_cast<bool>(basePageID != resolvedPageID); //instruction takes an additional cycle if adding Y changes the page          
            break;

        case AddressingMode::ZeroPageXIndexed:
            uint8_t ZeroPageAddressBase = static_cast<uint8_t>(instrBuffer[1]);
            uint8_t resolvedZeroPageAddress = ZeroPageAddressBase + RF.X.read(); // this may wraparound, but has no penalty as per documentation
            uint16_t resolvedAddress = static_cast<uint16_t>(ZEROPAGE_OFFSET) & static_cast<uint16_t>(resolvedZeroPageAddress); 
            operands.operandA = ram.readByte(resolvedAddress); // get byte from address
            break;
        
        case AddressingMode::ZeroPageYIndexed: // like for ZP X, but this is a rare addressing mode, per documentation
            uint8_t ZeroPageAddressBase = static_cast<uint8_t>(instrBuffer[1]);
            uint8_t resolvedZeroPageAddress = ZeroPageAddressBase + RF.Y.read(); // this may wraparound, but has no penalty as per documentation
            uint16_t resolvedAddress = static_cast<uint16_t>(ZEROPAGE_OFFSET) & static_cast<uint16_t>(resolvedZeroPageAddress); 
            operands.operandA = ram.readByte(resolvedAddress); // get byte from address
            break;

        case AddressingMode::Indirect: 
            // A note: this addressing mode is primarily used for JMP instructions: these are 3 byte instructions where the operand is an address to a 16b word which contains the effective target
            // for instance, performing JMP ($FF82) will result in a lookup at address $FF82. If $FF82 contains 0xC4 and $FF83 contains 0x80, then we resolve the operand/target as $80C4
            // NOTE per documentation: on NMOS variants, address of the lookup wraps around the zeropage, so JMP ($11FF) checks lookup at $11FF and $1100 rather than $11FF and $1200
            uint8_t highByteLookup;
            uint16_t resolvedAddressBase = concatenateWordFromTwoBytes(instrBuffer[2], instrBuffer[1]); // this is the address of our operand
            uint8_t lowByteLookup = ram.readByte(resolvedAddressBase); // low byte is already at lower address in both cases
            if (processorFamily == ChipType::NMOS6502){//bugged variant, wrap around if lower byte straddles page boundaries
                uint8_t pageOffsetLow = static_cast<uint8_t>(0x00FF & resolvedAddressBase); // keep lower byte only
                uint8_t pageOffsetHigh = pageOffsetLow + 1; // may wrap around or not
                uint16_t resolvedAddressHigh = (0xFF00 & resolvedAddressBase) & (static_cast<uint16_t>(pageOffsetHigh)); 
                uint8_t highByteLookup = ram.readByte(resolvedAddressHigh); 
                operands.operandPageCrossed = false;
            }
            else if (processorFamily ==  ChipType::CMOS6502){
                uint16_t resolvedAddressHigh = resolvedAddressBase + 1; //simple, bug corrected
                operands.operandPageCrossed = (ram.getPageIDFromAddress(resolvedAddressBase) != ram.getPageIDFromAddress(resolvedAddressHigh)); // if page is crossed, this takes an extra cycle
                uint8_t highByteLookup = ram.readByte(resolvedAddressHigh); 
            }
            else {throw std::runtime_error("Invalid Chip family declared. This error should not be throwable, something clearly went very wrong");}
            // now write to operand, with LSB in A slot and MSB in B
            operands.operandA = lowByteLookup;
            operands.operandB = highByteLookup;
            break;

        case AddressingMode::IndirectXIndexed:
            // Pre-indexed  X mode -> the specified address in a ZP address, to which the contents of X are added.  
            // The resultant address is itself a ZP address containing the address to look up for the resultant data
            uint16_t resolvedAddressBase = static_cast<uint16_t>(ZEROPAGE_OFFSET) & static_cast<uint16_t>(instrBuffer[1]);
            uint16_t resolvedAddress = (static_cast<uint16_t>(ZEROPAGE_OFFSET) & ((resolvedAddressBase + RF.X.read())& 0x00FF)); // Removes higher byte to ensure wraparound is performed when adding X
            // now look up data at ZP
            uint16_t lookupAddress = ram.readWord16b(resolvedAddress); //contains address of final target data
            operands.operandA = ram.readByte(lookupAddress);
            break;

        case AddressingMode::IndirectYIndexed:
            // Pose-indexed Y mode -> the specified address in a ZP address, used for lookup.  
            // The contents found at the lookup address are added to the contents of Y (check page change for extra cycle) which is used for final lookup
            uint16_t resolvedAddressBase = static_cast<uint16_t>(ZEROPAGE_OFFSET) & static_cast<uint16_t>(instrBuffer[1]);
            // now look up data at ZP
            uint16_t lookupAddressBase = ram.readWord16b(resolvedAddressBase); //contains address of final target data
            uint16_t lookupAddress = lookupAddressBase + static_cast<uint16_t>(RF.Y.read());
            operands.operandPageCrossed = (ram.getPageIDFromAddress(lookupAddressBase) != ram.getPageIDFromAddress(lookupAddress)); // if page crossed during +Y, add cycle penalty
            operands.operandA = ram.readByte(lookupAddress); //final lookup
            break;
        
        case AddressingMode::Relative:
            // used only for conditionnal branching. 
            ///NOTE: these are 2 byte instructions, with the operand being a SIGNED offset onto the incremented program counter,
            // eg BEQ 0x04 will (asssuming the condition is met) branch to PC + 2 + 0x04, so PC + 0x06
            int8_t offset = static_cast<int8_t>(instrBuffer[1]); // cast unsigned uint to signed int 
            uint16_t resolvedAddress = static_cast<int16_t>(RF.PC.readPC()) + 2 + offset; //NOTE: ChHECK THAT THIS IS THE DESIRED PC POLICY, EG THAT PC HAS NOT YET BEEN INCREMENTED YET
            operands.operandPageCrossed = (ram.getPageIDFromAddress(RF.PC.readPC() + 2) != ram.getPageIDFromAddress(resolvedAddress)); // add cycle penalty of +1 cycle (on TOP of branching penalty) if target is on different page
            // now write to operand, with LSB in A slot and MSB in B
            operands.operandA = fetchByteFromWord16b(resolvedAddress, byteSignificance::LOW);
            operands.operandB = fetchByteFromWord16b(resolvedAddress, byteSignificance::HIGH);
            break;
        
        default:
            break;
        };

    };

};