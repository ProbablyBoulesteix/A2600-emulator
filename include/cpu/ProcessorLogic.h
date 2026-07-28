// ProcessorLogic.h
#pragma once
#include <cpu/CPU.h>
#include <array>
#include <cpu/InstructionOps.h>
#include <cpu/RegisterFile.h>
#include <cpu/InstructionTypes.h>
#include <cpu/DecoderHelper.h>

std::array<Instruction, 256> makeOpCodeTable(); 
using OpCodeTableMap = std::array<Instruction, 256>;

class InstructionDecoder {};
