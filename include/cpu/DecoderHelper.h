// DecoderHelper.h
#pragma once
#include <cstdint>

class DecoderHelpers
{
protected:
    bool CheckPageCrossOffset(uint16_t baseAddress, uint8_t addressOffset);
    uint8_t ComputeTotalRuntimePageCross(uint16_t baseAddress, uint8_t addressOffset, uint8_t baseCycleCost, uint8_t pageCrossExtraCycles);

};