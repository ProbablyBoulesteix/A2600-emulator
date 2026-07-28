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
            .addressMode = AddressingMode::IndirectYIndexed,
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
            .readFlags = static_cast<FlagMask>(StatusFlag::C),
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
            .readFlags = static_cast<FlagMask>(StatusFlag::C),
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
            .readFlags = static_cast<FlagMask>(StatusFlag::Z),
            .writeFlags = 0,
            //.execute = &CPU::LDA,
        },

    // BIT (Test Bits in Memory with Accumulator)//
    // see documentation
    // N  Z C I D V
    // M7 + - - - M6
        [0x24] = {
            // Zeropage
            .opcode = 0xF0,
            .mnemonic = InstructionMnemonic::BIT,
            .addressMode = AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::V),
            //.execute = &CPU::LDA,
        },

        [0x2C] = {
            // absolute
            .opcode = 0xF0,
            .mnemonic = InstructionMnemonic::BIT,
            .addressMode = AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::V),
            //.execute = &CPU::LDA,
        },

    // BMI (Branch on Result Minus)//
    // BRANCH on N = 1
    // N Z C I D V
    // - - - - - -
        [0x30] = {
            // Relative
            .opcode = 0x30,
            .mnemonic = InstructionMnemonic::BMI,
            .addressMode = AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = static_cast<FlagMask>(StatusFlag::N),
            .writeFlags = 0,
            //.execute = &CPU::LDA,
        },
    
    // BNE (Branch Not Equal)//
    // BRANCH on Z = 0
    // N Z C I D V
    // - - - - - -
        [0xD0] = {
            // Relative
            .opcode = 0xD0,
            .mnemonic = InstructionMnemonic::BNE,
            .addressMode = AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = static_cast<FlagMask>(StatusFlag::Z),
            .writeFlags = 0,
            //.execute = &CPU::LDA,
        },

    // BPL (Branch on Result Plus)//
    // BRANCH on Z = 0
    // N Z C I D V
    // - - - - - -
        [0x10] = {
            // Relative
            .opcode = 0x10,
            .mnemonic = InstructionMnemonic::BPL,
            .addressMode = AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = static_cast<FlagMask>(StatusFlag::Z),
            .writeFlags = 0,
            //.execute = &CPU::LDA,
        },

    // BRK (Force Break)//
    // See documentation
    // N Z C I D V
    // - - - 1 - -
    // Push PC, Push SR
        [0x10] = {
            // Relative
            .opcode = 0x10,
            .mnemonic = InstructionMnemonic::BRK,
            .addressMode = AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 7,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::I),
            //.execute = &CPU::LDA,
        },
    
    // BVC (Branch on Overflow Clear)//
    // BRANCH on V = 0
    // N Z C I D V
    // - - - - - -
        [0x50] = {
            // Relative
            .opcode = 0x50,
            .mnemonic = InstructionMnemonic::BVC,
            .addressMode = AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = static_cast<FlagMask>(StatusFlag::V),
            .writeFlags = 0,
            //.execute = &CPU::LDA,
        },

    // BVS (Branch on Overflow Set)//
    // BRANCH on V = 1
    // N Z C I D V
    // - - - - - -
        [0x70] = {
            // Relative
            .opcode = 0x70,
            .mnemonic = InstructionMnemonic::BVS,
            .addressMode = AddressingMode::Relative,
            .byteCount = 2,
            .cycleCount = 2, //NOTE: DOC says that branch is 2 cycles + 1 if branching to same page and + 2 if branching to different page
            .additionalCyclesIfPageNotCrossed = 1,
            .additionalCyclesIfPageCrossed = 2,
            .readFlags = static_cast<FlagMask>(StatusFlag::V),
            .writeFlags = 0,
            //.execute = &CPU::LDA,
        },

    // CLC (Clear Carry FLag)//
    // 0 -> C
    // N Z C I D V
    // - - 0 - - -
        [0x18] = {
            // Relative
            .opcode = 0x18,
            .mnemonic = InstructionMnemonic::CLC,
            .addressMode = AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::C),
            //.execute = &CPU::LDA,
        },
    // CLD (Clear Decimal Mode)//
    // 0 -> D
    // N Z C I D V
    // - - - - 0 -
        [0xD8] = {
            // Relative
            .opcode = 0xD8,
            .mnemonic = InstructionMnemonic::CLD,
            .addressMode = AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::D),
            //.execute = &CPU::LDA,
        },
    // CLI (Clear Interrupt Disable Bit)//
    // 0 -> I
    // N Z C I D V
    // - - - 0 - -
        [0x58] = {
            // Relative
            .opcode = 0x58,
            .mnemonic = InstructionMnemonic::CLI,
            .addressMode = AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::I),
            //.execute = &CPU::LDA,
        },
    // CLV (Clear Overflow flag)//
    // 0 -> V
    // N Z C I D V
    // - - - 0 - -
        [0xB8] = {
            // Relative
            .opcode = 0xB8,
            .mnemonic = InstructionMnemonic::CLV,
            .addressMode = AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::V),
            //.execute = &CPU::LDA,
        },

    // CMP (Compare Memory with Accumulator)//
    // A - M
    // N Z C I D V
    // + + + - - -
        [0xC9] = {
            // Immediate
            .opcode = 0xC9,
            .mnemonic = InstructionMnemonic::CMP,
            .addressMode = AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C),
            //.execute = &CPU::LDA,
        },

        [0xC5] = {
            // Zeropage
            .opcode = 0xC5,
            .mnemonic = InstructionMnemonic::CMP,
            .addressMode = AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C),
            //.execute = &CPU::LDA,
        },
        [0xD5] = {
            // Zeropage X
            .opcode = 0xD5,
            .mnemonic = InstructionMnemonic::CMP,
            .addressMode = AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C),
            //.execute = &CPU::LDA,
        },

        [0xCD] = {
            // Absolute
            .opcode = 0xCD,
            .mnemonic = InstructionMnemonic::CMP,
            .addressMode = AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C),
            //.execute = &CPU::LDA,
        },

        [0xDD] = {
            // Absolute X
            .opcode = 0xDD,
            .mnemonic = InstructionMnemonic::CMP,
            .addressMode = AddressingMode::AbsoluteXIndexed,
            .byteCount = 2,
            .cycleCount = 4, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C),
            //.execute = &CPU::LDA,
        },

        [0xD9] = {
            // Absolute Y
            .opcode = 0xD9,
            .mnemonic = InstructionMnemonic::CMP,
            .addressMode = AddressingMode::AbsoluteYIndexed,
            .byteCount = 3,
            .cycleCount = 4, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C),
            //.execute = &CPU::LDA,
        },
        [0xC1] = {
            // Indirect X
            .opcode = 0xC1,
            .mnemonic = InstructionMnemonic::CMP,
            .addressMode = AddressingMode::IndirectXIndexed,
            .byteCount = 2,
            .cycleCount = 6, 
            .additionalCyclesIfPageCrossed = 0,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C),
            //.execute = &CPU::LDA,
        },

        [0xD1] = {
            // Indirect Y
            .opcode = 0xD1,
            .mnemonic = InstructionMnemonic::CMP,
            .addressMode = AddressingMode::IndirectYIndexed,
            .byteCount = 2,
            .cycleCount = 5, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C),
            //.execute = &CPU::LDA,
        },

    // CPX (Compare Memory with X)//
    // X - M
    // N Z C I D V
    // + + + - - -
        [0xE0] = {
            // Immediate
            .opcode = 0xE0,
            .mnemonic = InstructionMnemonic::CPX,
            .addressMode = AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C),
            //.execute = &CPU::LDA,
        },

        [0xE4] = {
            // Zeropage
            .opcode = 0xE4,
            .mnemonic = InstructionMnemonic::CPX,
            .addressMode = AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C),
            //.execute = &CPU::LDA,
        },
        [0xEC] = {
            // Absolute
            .opcode = 0xEC,
            .mnemonic = InstructionMnemonic::CPX,
            .addressMode = AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z) | static_cast<FlagMask>(StatusFlag::C),
            //.execute = &CPU::LDA,
        },

    // DEC (Decrement by one)//
    // M - 1 -> M
    // N Z C I D V
    // + + - - - -
        [0xC6] = {
            // Zeropage
            .opcode = 0xC6,
            .mnemonic = InstructionMnemonic::DEC,
            .addressMode = AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 5, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },

        [0xD6] = {
            // Zeropage X
            .opcode = 0xD6,
            .mnemonic = InstructionMnemonic::DEC,
            .addressMode = AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 6, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0xCE] = {
            // Absolute
            .opcode = 0xCE,
            .mnemonic = InstructionMnemonic::DEC,
            .addressMode = AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 6, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0xDE] = {
            // Absolute X
            .opcode = 0xDE,
            .mnemonic = InstructionMnemonic::DEC,
            .addressMode = AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 7, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },

    // DEX (Decrement X by one)//
    // X - 1 -> X
    // N Z C I D V
    // + + - - - -
        [0xCA] = {
            // Implied
            .opcode = 0xCA,
            .mnemonic = InstructionMnemonic::DEX,
            .addressMode = AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
    // DEY (Decrement Y by one)//
    // Y - 1 -> Y
    // N Z C I D V
    // + + - - - -
        [0x88] = {
            // Implied
            .opcode = 0x88,
            .mnemonic = InstructionMnemonic::DEY,
            .addressMode = AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },

    // EOR (Exclusive OR with Accumulator)//
    // A XOR M -> A
    // N Z C I D V
    // + + - - - -
        [0x49] = {
            // Immediate
            .opcode = 0x49,
            .mnemonic = InstructionMnemonic::EOR,
            .addressMode = AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x45] = {
            // ZP
            .opcode = 0x45,
            .mnemonic = InstructionMnemonic::EOR,
            .addressMode = AddressingMode::ZeroPage,
            .byteCount = 2,
            .cycleCount = 3, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x55] = {
            // ZP X
            .opcode = 0x55,
            .mnemonic = InstructionMnemonic::EOR,
            .addressMode = AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x4D] = {
            // ABS
            .opcode = 0x4D,
            .mnemonic = InstructionMnemonic::EOR,
            .addressMode = AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 4, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x5D] = {
            // ABS X
            .opcode = 0x5D,
            .mnemonic = InstructionMnemonic::EOR,
            .addressMode = AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 4, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x59] = {
            // ABS Y
            .opcode = 0x59,
            .mnemonic = InstructionMnemonic::EOR,
            .addressMode = AddressingMode::AbsoluteYIndexed,
            .byteCount = 3,
            .cycleCount = 4, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x41] = {
            // Indirect X
            .opcode = 0x41,
            .mnemonic = InstructionMnemonic::EOR,
            .addressMode = AddressingMode::IndirectXIndexed,
            .byteCount = 2,
            .cycleCount = 6, 
            .additionalCyclesIfPageCrossed = 0,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },
        [0x51] = {
            // Indirect Y
            .opcode = 0x51,
            .mnemonic = InstructionMnemonic::EOR,
            .addressMode = AddressingMode::IndirectYIndexed,
            .byteCount = 2,
            .cycleCount = 6, 
            .additionalCyclesIfPageCrossed = 1,
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },

    // INC (INCREMENT Memeory by One)//
    // M + 1 -> M
    // N Z C I D V
    // + + - - - -
        [0xE6] = {
            // Zeropage
            .opcode = 0xE6,
            .mnemonic = InstructionMnemonic::INC,
            .addressMode = AddressingMode::Immediate,
            .byteCount = 2,
            .cycleCount = 5, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },   
        [0xF6] = {
            // Zeropage X
            .opcode = 0xF6,
            .mnemonic = InstructionMnemonic::INC,
            .addressMode = AddressingMode::ZeroPageXIndexed,
            .byteCount = 2,
            .cycleCount = 6, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },  
        [0xEE] = {
            // Absolute
            .opcode = 0xEE,
            .mnemonic = InstructionMnemonic::INC,
            .addressMode = AddressingMode::Absolute,
            .byteCount = 3,
            .cycleCount = 6, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },   
        [0xFE] = {
            // Zeropage X
            .opcode = 0xFE,
            .mnemonic = InstructionMnemonic::INC,
            .addressMode = AddressingMode::AbsoluteXIndexed,
            .byteCount = 3,
            .cycleCount = 7, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },  
    // INX (INCREMENT X by One)//
    // X + 1 -> X
    // N Z C I D V
    // + + - - - -
        [0xE8] = {
            // Implied
            .opcode = 0xE8,
            .mnemonic = InstructionMnemonic::INX,
            .addressMode = AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },  
    // INY (INCREMENT Y by One)//
    // Y + 1 -> Y
    // N Z C I D V
    // + + - - - -
        [0xC8] = {
            // Implied
            .opcode = 0xC8,
            .mnemonic = InstructionMnemonic::INY,
            .addressMode = AddressingMode::Implied,
            .byteCount = 1,
            .cycleCount = 2, 
            .readFlags = 0,
            .writeFlags = static_cast<FlagMask>(StatusFlag::N) | static_cast<FlagMask>(StatusFlag::Z),
            //.execute = &CPU::LDA,
        },  

};