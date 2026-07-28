// Registers.h
#pragma once
#include <cstdint>

class RegisterFile {
public:
    struct Register {
        uint8_t value = 0;

        void Clear() {
            value = 0;
        }
    };

    struct StatusRegister{
        uint8_t status = 0; //FIXME: check what the default 6502 init is for status registers
    };

    struct ProgramCounter{
        // FIXME: check 6502 init
        uint8_t PCH = 0; // PC High byte (lower address in BE convention)
        uint8_t PCL = 0; // PC Low byte (higher address in BE convention)
        uint16_t PC = 0;

        // ISSUE: these values should not be handled directly to avoid sync issues, so prefferable to read/write via methods
        void IncrementPC(int PCoffset = 2) {
            PC = PC + PCoffset; //classically, this is PC +2
            // extract bit fields
            PCH = PC & 0xFF00; // AND with 0b1111.1111.0000.0000 to get upper byte
            PCL = PC & 0x00FF; // AND with 0b000.0000.1111.1111 to get lower byte
        };

        uint16_t ComputePCOffset(int PCOffset){
            // Compute PC offset at PC + N and returns value but does NOT commit/increment PC
            uint16_t nextPC;
            nextPC = PC + PCOffset;
            return nextPC;
        };
    };

    struct StatusRegister{
        uint8_t status; /// CHECK 6502 init later
        // maybe add set/clear routines here later, for now this is simple wrapper
    };

    struct StackPointer{
        uint16_t stack_address; // check default 6502 stack pointer here
        // FIXME: check stack conventions for 6502 here later
    };
    // General purpose registers
    Register A; // Accumulator
    Register X; // Index Register X
    Register Y; // Index Register Y
    // Special registers
    ProgramCounter PC; // Program counter
    StatusRegister SR; // Status Register
    StackPointer SP; // Stack Pointer
};