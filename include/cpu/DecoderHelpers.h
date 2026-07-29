// DecoderHelpers.h
#pragma once
#include <cstdint>
#include <stdint.h>
#include <cpu/DecoderHelpers.h>



class DecoderHelpers
{
protected:

    bool CheckPageCrossOffset(uint16_t baseAddress, uint8_t addressOffset);
    uint8_t ComputeTotalRuntimePageCross(uint16_t baseAddress, uint8_t addressOffset, uint8_t baseCycleCost, uint8_t pageCrossExtraCycles);
    bool checkIfDataZero(uint8_t data);
    bool checkIfDataNegative(uint8_t data);

    bool checkIfOperationCarry(uint8_t operandA, uint8_t operandB, bool carryBit = 0);
    bool checkIfOperationOverflow(uint8_t operandA, uint8_t operandB, bool carryBit = 0);



};