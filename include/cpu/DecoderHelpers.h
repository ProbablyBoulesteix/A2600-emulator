// DecoderHelpers.h
#pragma once
#include <cstdint>
#include <vector>
#include <optional>
#include <stdint.h>
#include <cpu/DecoderHelpers.h>
#include <cpu/ProcessorLogic.h>
#include <cpu/InstructionTypes.h>
#include <memory/ram.h>
#include <cpu/RegisterFile.h>

struct FlagResult { // short system for tracking flags
    std::optional<uint8_t> znSource;  //which byte should be used for deriving the Z and N flags?
    std::optional<bool> carry;
    std::optional<bool> overflow;
};

class DecoderHelpers
{
protected:

    bool CheckPageCrossOffset(uint16_t baseAddress, uint8_t addressOffset);
    uint8_t ComputeTotalRuntimePageCross(uint16_t baseAddress, uint8_t addressOffset, uint8_t baseCycleCost, uint8_t pageCrossExtraCycles);
    bool checkIfDataZero(uint8_t data);
    bool checkIfDataNegative(uint8_t data);

    bool checkIfOperationCarry(uint8_t operandA, uint8_t operandB, bool carryBit = 0);
    bool checkIfOperationOverflow(uint8_t operandA, uint8_t operandB, bool carryBit = 0);
    OperandData fetchOperands(const Instruction& instr, uint16_t baseAddress, Memory& ram, RegisterFile& RF, ChipType processorFamily = ChipType::NMOS6502);




};