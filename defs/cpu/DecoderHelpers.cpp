// DecoderHelpers.cpp

#include <stdint.h>
#include <cpu/DecoderHelpers.h>


class DecoderHelpers{
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
};