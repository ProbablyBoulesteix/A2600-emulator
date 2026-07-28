
/*
* AUTHOR: Emma BOULESTEIX
* DATE: Aug 2026
* PROJECT: A2600 CPU emulator
*/
#include <stdint.h>
#include <array>
#include <format>
#include <stdexcept>

class Memory{
    uint8_t* ramBuffer; //pointer to where RAM is
public:
    Memory(uint16_t memorySizeInBytes){
        ramBuffer = (uint8_t*)malloc(sizeof(uint8_t) * memorySizeInBytes);
        // Check for null pointers first to ensure memory has been allocated properly
        if (ramBuffer == nullptr) {
            throw std::runtime_error(std::format("[Constructor@Memory | NULL PTR] ERROR: Could not allocate memory of size {} Bytes\n", ((int)(sizeof(uint8_t) * memorySizeInBytes))));
        };
    };

};