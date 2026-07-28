/*
* AUTHOR: Emma BOULESTEIX
* DATE: Aug 2026
* PROJECT: A2600 CPU emulator
* FILE: Contains the definitions for each instruction though not the CPU macros (eg CPU::LDA)
*/

// InstructionOps.h
#pragma once
#include <stdint.h>
#include <cpu/CPU.h>
#include <cpu/InstructionTypes.h>


//FIXME: All cpu instruction pointers are currently blanked out due to them not being defined. Fix later.
const Instruction opcodeTable[256]{
    
    // ADC (Add Memory to Accumulator with Carry)//
    // A + M + C -> A, C
    // N Z C I D V
    // + + + - - +
        [0x69] = {
            // Immediate mode
            .opcode = 0x69,
            .mnemonic = InstructionMnemonic::LDA,
            .addressMode = AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2,
            .readFlags = static_cast<FlagMask>(StatusFlag::C),
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C) | static_cast<FlagMask>(StatusFlag::V),
            //.execute = &CPU::LDA,
        },
        [0x65] = {
            // Zeropage mode
            .opcode = 0x65,
            .mnemonic = InstructionMnemonic::LDA,
            .addressMode = AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3,
            .readFlags = static_cast<FlagMask>(StatusFlag::C),
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C) | static_cast<FlagMask>(StatusFlag::V),
            //.execute = &CPU::LDA,
        },
        [0x75] = {
            // Zeropage mode, X
            .opcode = 0x75,
            .mnemonic = InstructionMnemonic::LDA,
            .addressMode = AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 4,
            .readFlags = static_cast<FlagMask>(StatusFlag::C),
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C) | static_cast<FlagMask>(StatusFlag::V),
            //.execute = &CPU::LDA,
        },
        [0x6D] = {
            // Absolute Mode
            .opcode = 0x6D,
            .mnemonic = InstructionMnemonic::LDA,
            .addressMode = AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4,
            .readFlags = static_cast<FlagMask>(StatusFlag::C),
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C) | static_cast<FlagMask>(StatusFlag::V),
            //.execute = &CPU::LDA,
        },

        [0x7D] = {
            // Absolute Mode, X
            .opcode = 0x7D,
            .mnemonic = InstructionMnemonic::LDA,
            .addressMode = AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 4,
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = static_cast<FlagMask>(StatusFlag::C),
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C) | static_cast<FlagMask>(StatusFlag::V),
            //.execute = &CPU::LDA,
        },
        [0x79] = {
            // Absolute Mode, Y
            .opcode = 0x79,
            .mnemonic = InstructionMnemonic::LDA,
            .addressMode = AddressingMode::AbsoluteYIndexed,
            .byteCount = 3,
            .cycleCount = 4,
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = static_cast<FlagMask>(StatusFlag::C),
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C) | static_cast<FlagMask>(StatusFlag::V),
            //.execute = &CPU::LDA,
        },
        [0x61] = {
            // Indirect Mode, X
            .opcode = 0x61,
            .mnemonic = InstructionMnemonic::LDA,
            .addressMode = AddressingMode::AbsoluteXIndexed,
            .byteCount = 2,
            .cycleCount = 6,
            .readFlags = static_cast<FlagMask>(StatusFlag::C),
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C) | static_cast<FlagMask>(StatusFlag::V),
            //.execute = &CPU::LDA,
        },
        [0x71] = {
            // Indirect Mode, Y
            .opcode = 0x71,
            .mnemonic = InstructionMnemonic::LDA,
            .addressMode = AddressingMode::AbsoluteXIndexed,
            .byteCount = 2,
            .cycleCount = 5,
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = static_cast<FlagMask>(StatusFlag::C),
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C) | static_cast<FlagMask>(StatusFlag::V),
            //.execute = &CPU::LDA,
        },

    // AND (AND Memory with Accumulator)//
    // A AND M -> A
    // N Z C I D V
    // + + - - - -

        [0x29] = {
            // Immediate
            .opcode = 0x29,
            .mnemonic = InstructionMnemonic::AND,
            .addressMode = AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x25] = {
            // ZeroPage
            .opcode = 0x25,
            .mnemonic = InstructionMnemonic::AND,
            .addressMode = AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x35] = {
            // ZeroPage, X
            .opcode = 0x35,
            .mnemonic = InstructionMnemonic::AND,
            .addressMode = AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 4,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x2D] = {
            // Absolute
            .opcode = 0x2D,
            .mnemonic = InstructionMnemonic::AND,
            .addressMode = AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x3D] = {
            // Absolute X
            .opcode = 0x3D,
            .mnemonic = InstructionMnemonic::AND,
            .addressMode = AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 4,
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x39] = {
            // Absolute Y
            .opcode = 0x39,
            .mnemonic = InstructionMnemonic::AND,
            .addressMode = AddressingMode::AbsoluteYIndexed,
            .byteCount = 3,
            .cycleCount = 4,
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x21] = {
            // Indirect X
            .opcode = 0x21,
            .mnemonic = InstructionMnemonic::AND,
            .addressMode = AddressingMode::IndirectXIndexed,
            .byteCount = 2,
            .cycleCount = 6,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x31] = {
            // Indirect Y
            .opcode = 0x31,
            .mnemonic = InstructionMnemonic::AND,
            .addressMode = AddressingMode::IndirectYindexed,
            .byteCount = 2,
            .cycleCount = 5,
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },

    // BCC (Branch on Carry Clear)//
    // BRANCH on C = 0
    // N Z C I D V
    // - - - - - -
        [0x90] = {
            // Relative
            .opcode = 0x90,
            .mnemonic = InstructionMnemonic::BCC,
            .addressMode = AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::LDA,
        },

    // BCS (Branch on Carry Set)//
    // BRANCH on C = 1
    // N Z C I D V
    // - - - - - -
        [0xB0] = {
            // Relative
            .opcode = 0xB0,
            .mnemonic = InstructionMnemonic::BCS,
            .addressMode = AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::LDA,
        },
    // BEQ (Branch on Result Zero)//
    // BRANCH on Z = 1
    // N Z C I D V
    // - - - - - -
        [0xF0] = {
            // Relative
            .opcode = 0xF0,
            .mnemonic = InstructionMnemonic::BEQ,
            .addressMode = AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = 0,
            .writeFlags = 0,
            //.execute = &CPU::LDA,
        },

};