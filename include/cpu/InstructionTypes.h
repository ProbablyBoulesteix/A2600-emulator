/*
* AUTHOR: Emma BOULESTEIX
* DATE: Aug 2026
* PROJECT: A2600 CPU emulator
* FILE: Contains type and class definitions for the CPU decoder
*/
// InstructionTypes.h

#pragma once
#include <cstdlib>
#include <cstdint>
#include <cpu/InstructionOps.h>
#include <cpu/CPU.h>


/*
NOTE: This file includes all definitions and type defs for the 6502 instructions. It is is based on the ressource found here (https://www.masswerk.at/6502/6502_instruction_set.html).
The A2600 uses a limited variant of the 6502 called the 6507, which doesn't include BCD instructions and uses a 12bit (4096B) address space: we will thus implement the 6502 instruction set ONLY and remove the BCD instructions
*/

enum AddressingMode{
    // All the 6502 addressing modes 
    Accumulator,
    Absolute,
    AbsoluteXIndexed,
    AbsoluteYIndexed,
    Immediate,
    Implied,
    Indirect,
    IndirectXIndexed,
    IndirectYIndexed,
    Relative,
    ZeroPage,
    ZeroPageXIndexed,
    ZeroPageYIndexed
};

enum class StatusFlag : uint8_t {
    // This enum defines all flags the 6502/6507 SR uses, and the relevant 8bit bitmask 
    C = 1 << 0, // Carry flag, at bit 0 (LSB)
    Z = 1 << 1, // Zero flag
    I = 1 << 2, // Interrupt flAG
    D = 1 << 3, // Decimal flag (technically irrelevant for A2600)
    B = 1 << 4, // Break flag
    V = 1 << 6, // Overflow flag
    N = 1 << 7, // Negative flag, at bit 7 (MSB)
};
using FlagMask = uint8_t; // TYPEDEF: FlagMask aliases 8bit uint8 and represents a mask on the 6502 Status register

enum InstructionMnemonic{ 
    // Common 6502 Assembler mnemonics, for easier debugging
    ADC,    // ADD with Carry
    AND,    // AND with Accumulator
    ASL,    // Arithmetic SHIFT left
    BCC,    // BRANCH on Carry Clear
    BCS,    // BRANCH on Carry Set
    BEQ,    // BRANCH on Equal (zero-zet)
    BIT,    // Bit TEST
    BMI,    // BRANCH on MINUS (negative set)
    BNE,    // BRANCH on Not Equal (Zero clear)
    BPL,    // BRANCH on PLUS (negative clear)
    BRK,    // Break/Interrupt
    BVC,    // BRANCH on Overflow Clear 
    BVS,    // BRANCH on Overflow Set
    CLC,    // CLEAR CARRY
    CLD,    // CLEAR decimal
    CLI,    // CLEAR interrupt disable
    CLV,    // CLEAR Overflow
    CMP,    // COMPARE with Accumulator
    CPX,    // COMPARE with X
    CPY,    // COMPARE with Y
    DEC,    // DECREMENT
    DEX,    // DECREMENT X
    DEY,    // DECREMENT Y
    EOR,    // XOR with Accumulator
    INC,    // INCREMENT
    INX,    // INCREMENT X
    INY,    // INCREMENT Y
    JMP,    // JUMP
    JSR,    // JUMP Subroutine
    LDA,    // LOAD Accumulator
    LDX,    // LOAD X 
    LDY,    // LOAD Y
    LSR,    // Logical SHIFT Right
    NOP,    // No-Operation
    ORA,    // OR with Accumulator
    PHA,    // PUSH Accumulator
    PHP,    // PUSH Processor Status (SR)
    PLA,    // PULL Accumulator
    PLP,    // PULL Processor Status (SR)
    ROL,    // ROTATE Left
    ROR,    // ROTATE Right
    RTI,    // RETURN from Interrupt
    RTS,    // RETURN from Subroutine
    SBC,    // SUBTRACT with Carry
    SEC,    // SET Carry,
    SED,    // SET Decimal
    SEI,    // SET INTERRUPT Disable
    STA,    // STORE Accumulator
    STX,    // STORE Register
    STY,    // STORE Y Register
    TAX,    // TRANSFER Accumulator to X
    TAY,    // TRANSFER Accumulator to Y
    TSX,    // TRANSFER Stack Pointer to X
    TXA,    // TRANSFER X to Accumulator
    TXS,    // TRANSFER X to Stack Pointer
    TYA,    // TRANSFER Y to Accumulator
};

struct Instruction{ // Encode all 6502 instruction metadata here 
    // Info about instruction itself
    uint8_t opcode; // pure 6502 binary opcode
    InstructionMnemonic mnemonic; // instruction mnemonic here
    AddressingMode addressMode; // 
    uint8_t byteCount; // how many bites does this take
    uint8_t cycleCount; // how many cycles does the instruction take to execute?
    uint8_t additionalCyclesIfPageNotCrossed = 0; // Useful for branching, dictates how many cycles op should take if on same page
    uint8_t additionalCyclesIfPageCrossed = 0; // Particularly important for memory, brach and zero page operations: if computed address is in a different page (eg a different 256B chunk), how many more cycles should execution take?
    // Register level information, write expressions like: static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z)
    FlagMask readFlags;
    FlagMask writeFlags;
    void (CPU::*execute)(const Instruction&); // Structure: this is a pointer to a method in the main CPU class which takes in an instruction
};

extern const Instruction opcodeTable[256]; // Declaring an array of instructions for InstructionOps.h... idea is that I can do opcodeTable[Instruction_LDA] or something and get back all relevant info