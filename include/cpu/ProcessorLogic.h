// ProcessorLogic.h
#pragma once
#include <array>
#include <cpu/InstructionTypes.h>
#include <cpu/InstructionOps.h>

std::array<Instruction, 256> makeOpCodeTable(); 
using OpCodeTableMap = std::array<Instruction, 256>;

class InstructionDecoder {};
