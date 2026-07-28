/*
* AUTHOR: Emma BOULESTEIX
* DATE: Aug 2026
* PROJECT: A2600 CPU emulator
* FILE: Contains the definitions for each instruction though not the CPU macros (eg CPU::LDA)
*/

#include <stdint.h>
#include <cpu/ProcessorLogic.h>

// Base Class: Decoder and related functions
class InstructionDecoder : DecoderHelpers {
    // References to processor register file, opcode mapper and CPU type here
    OpCodeTableMap OpCMap;
    RegisterFile RF;
    ChipType CpuTypeFamily;
public:
// constructor where references to ressources are passed 
    InstructionDecoder(RegisterFile& CPURF,  OpCodeTableMap& CPUOpCMap, ChipType CPUType = ChipType::NMOS6502){
        OpCMap = CPUOpCMap; //opcode <-> instruction mapping
        RF = CPURF; // Register File
        CpuTypeFamily = CPUType; // Not sure if this will be of any use yet, but toggles the CPU type
    };
// Setting this as PROTECTED because this will be inherinted by Processor class. These are individual instruction handlers (eg LDA, LDX...)
protected:
    //void ADC();


    


};