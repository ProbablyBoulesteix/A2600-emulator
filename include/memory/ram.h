// ram.h
#pragma once
#include <stdint.h>
#include <array>
#include <vector>

enum CPUEndianness {
    BIG,
    LITTLE,
};

class Memory{
public:
    Memory(uint16_t memorySizeInBytes); //constructor
    uint8_t getPageIDFromAddress(uint16_t address) const;
    std::vector<uint8_t> fetchBytes(uint16_t address, uint8_t byteCount, CPUEndianness endianConvention = CPUEndianness::BIG) ;
    uint8_t readByte(uint16_t address) const;
    uint16_t readWord16b(uint16_t address);
    void writeByte(uint16_t address, uint8_t dataByte);
    void writeWord16b(uint16_t address, uint16_t dataWord);

};