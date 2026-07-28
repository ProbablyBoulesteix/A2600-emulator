// DecoderHelpers.cpp

#include <stdint.h>


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
};