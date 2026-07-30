/*
* AUTHOR: Emma BOULESTEIX
* DATE: Aug 2026
* PROJECT: A2600 CPU emulator
* FILE: Contains the definitions for each instruction though not the CPU macros (eg CPU::LDA)
*/

#include <stdint.h>
#include <optional>

#include <cpu/ProcessorLogic.h>
#include <cpu/CPU.h>
#include <cpu/InstructionOps.h>
#include <cpu/RegisterFile.h>
#include <cpu/InstructionTypes.h>
#include <cpu/DecoderHelpers.h>
#include <cpu/RegisterFile.h>
#include <memory/ram.h>
#include <stdexcept>
#include <misc/BCDHelpers.h>



#define ZEROPAGE_OFFSET 0x0000 //zeropage addresses are from 0x0000-0x00FF

struct ResolvedInfoInstruction{ //metadata helper system: when running, the executor can add a bunch of data here relating to the cycle count for this instruction
    Instruction instruc; //all data about the instruction's routines
    bool isPrimedData = false; //is data stale? may be commented out later
    uint8_t resolvedCycleCount; //how many cycles does this specific instruciton take?
    uint8_t runningCyclesTally = 0; //not used by this class, but can be pinged by timer to keep track of how long this instruction has been running
    uint8_t resolvedByteCount; //how many bytes is the instruction, INCLUDING opcode?
    std::optional<uint8_t> znSource; // byte to derive N/Z from
    std::optional<bool> carry;
    std::optional<bool> overflow;
    std::optional<bool> zero;
    std::optional<bool> negative;
public:
    void resetRunningPrimed() {runningCyclesTally = 0;}; // for timer, reset tally of running cycles
    bool incrementAndCheckTallyStale(){ //increments tally, and then returns true if we've hit the number of cycle deeded
        runningCyclesTally++;
        return (runningCyclesTally >= resolvedCycleCount);
    };
};

// Base Class: Decoder and related functions
class InstructionDecoder : DecoderHelpers {
    // References to processor register file, opcode mapper and CPU type here
    OpCodeTableMap& OpCMap;
    RegisterFile& RF;
    ChipType CpuTypeFamily;
    Memory& RAM;


public:
// constructor where references to ressources are passed 
    InstructionDecoder(RegisterFile& CPURF,  OpCodeTableMap& CPUOpCMap, Memory& systemRAM, ChipType CPUType = ChipType::NMOS6502) : RF(CPURF), OpCMap(CPUOpCMap), RAM(systemRAM), CpuTypeFamily(CPUType){};
    //From the emulator's perspective, these executors run atomically, so a 6 cycle instruction runs all at once THEN stalls for 
    ResolvedInfoInstruction instructionMetadata; //GOAL: the executors below just do flag ops and basic math and state changes, with timing done by the overall system timer. 

   
// Setting this as PROTECTED because this will be inherinted by Processor class. These are individual instruction handlers (eg LDA, LDX...)
    void ADC(Instruction instr){
        instructionMetadata.resolvedByteCount = instr.byteCount; //includes opcode AND operands
        AddressingMode instructionMode = instr.addressMode;
        // ADC supports Imm, ZP(-,X), ABS(-,X,Y) and INDIRECT(X,Y) modes
        OperandData data = fetchOperands(instr, RF.PC.readPC(), RAM, RF, CpuTypeFamily); // get operands for ADC
        // ADC is A + M + C -> A, C
        // check against conditionnals
        uint8_t result, newFlags, cycleCost;
        bool isCarry, isOverflow, isZero, isNegative;
        bool isDecimal = RF.SR.readFlag(StatusFlag::D);
        //FIXME: ADD BCD FUNCTIONALITY
        if (data.operandA.has_value() && (!isDecimal)){ //sanity check, should always be set anyway
            result = RF.A.read() + data.operandA.value() + RF.SR.readFlag(StatusFlag::C);
            isCarry = checkIfOperationCarry(RF.A.read(),data.operandA.value(), RF.SR.readFlag(StatusFlag::C));
            isOverflow = checkIfOperationOverflow(RF.A.read(),data.operandA.value(), RF.SR.readFlag(StatusFlag::C));
            isZero = checkIfDataZero(result);
            isNegative = checkIfDataNegative(result);
        }
        else if (data.operandA.has_value() && (isDecimal)) // of note: NMOS 6502 computes N and V BASED on bitwise representation, NOT decimal ones
        {   
            BCD8 Acc = BCD8(RF.A.read());
            BCD8 Op = BCD8(data.operandA.value());
            BCD8 Carry = BCD8(static_cast<uint8_t>(RF.SR.readFlag(StatusFlag::C)));
            //result = BCD8::addBCD(RF.A.read(), data.operandA.value());
            // result = A + M + C
            Acc = Acc.operator+(Op); 
            Acc = Acc.operator+(Carry);

            //now compute flags
            isCarry = (Acc.toBinary() >= 100); // carry if BCD exceeds 99
            isZero = checkIfDataZero(Acc.toBinary());
            isNegative = checkIfDataNegative(Acc.toBinary()); //FIXME: check later
            if (CpuTypeFamily == ChipType::NMOS6502){isOverflow = checkIfOperationOverflow(RF.A.read(),data.operandA.value(), RF.SR.readFlag(StatusFlag::C))}; //BUG in original NMOS 6502
            else if (CpuTypeFamily == ChipType::CMOS6502)
            {
                /* code */
            }
            
        }
        
        else {throw std::runtime_error("ERROR: invalid payload for operands");} // should not occur if all goes well
        if (data.operandPageCrossed.has_value()){ // check now to see if a page crossing occured for the relevant instructions
            cycleCost = instr.cycleCount + static_cast<uint8_t>(data.operandPageCrossed.value()); // ALL ADC instructions either have no penalty OR a 1 cycle penalty for page crossing
        }
        else {cycleCost = instr.cycleCount;} // no page crossed, implicit from addressing mode so no penalty
        instructionMetadata = makeInstructionMetaData(instr, cycleCost, result, isCarry, isOverflow, isZero, isNegative); //payload goes here
        // now commit flags
        RF.SR.commitFlags(instr, instructionMetadata); // commit N,Z, C and V flags
        RF.A.write(result);

    };
    
private:
    ResolvedInfoInstruction makeInstructionMetaData(Instruction instr, uint8_t resolvedCycleCount, uint8_t resultByte, bool isCarry = false, bool isOverflow = false, bool isZero = false, bool isNegative = false){
        ResolvedInfoInstruction payload;
        payload.instruc = instr;
        payload.carry = isCarry;
        payload.overflow = isOverflow;
        payload.znSource = resultByte;
        payload.zero = isZero;
        payload.negative = isNegative;
        payload.isPrimedData = true;
        return payload;
    };

};