// ProcessorLogic.h
#pragma once
#include <array>
#include <optional>
#include <cpu/InstructionTypes.h>
#include <cpu/InstructionOps.h>

std::array<Instruction, 256> makeOpCodeTable(); 
using OpCodeTableMap = std::array<Instruction, 256>;

class InstructionDecoder {
private:
    ResolvedInfoInstruction makeInstructionMetaData(Instruction instr, uint8_t resolvedCycleCount, uint8_t resultByte, bool isCarry = false, bool isOverflow = false, bool isZero = false, bool isNegative = false );
};



struct ResolvedInfoInstruction{ //metadata helper system: when running, the executor can add a bunch of data here relating to the cycle count for this instruction
    Instruction instruc; //all data about the instruction's routines
    uint8_t resolvedCycleCount; //how many cycles does this specific instruciton take?
    uint8_t runningCyclesTally = 0; //not used by this class, but can be pinged by timer to keep track of how long this instruction has been running
    uint8_t resolvedByteCount; //how many bytes is the instruction, INCLUDING opcode?
    std::optional<uint8_t> znSource; // byte to derive N/Z from
    std::optional<bool> carry;
    std::optional<bool> overflow;
    std::optional<bool> zero;
    std::optional<bool> negative;
public:
    void resetRunningPrimed(); // for timer, reset tally of running cycles
    bool incrementAndCheckTallyStale();
    
};

struct OperandData{
    std::optional<AddressingMode> resolvedAddressingMode;
    std::optional<uint8_t> operandA;
    std::optional<uint8_t> operandB;
    std::optional<bool> insructionPageCrossed;
    std::optional<bool> operandPageCrossed;

};
