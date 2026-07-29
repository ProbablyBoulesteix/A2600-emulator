// miscHelpers.h
#pragma once
#include <stdint.h>

enum byteSignificance {
    HIGH,
    LOW,
};

class BinaryHelpers {
public:
    uint8_t fetchByteFromWord16b(uint16_t word, byteSignificance byte);
    uint16_t concatenateWordFromTwoBytes(uint8_t highByte, uint8_t lowByte);
};