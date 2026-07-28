// Registers.h

#pragma once

#include <cpu/RegisterFile.h>
#include <stdint.h>

class RegisterFile {
public:
    struct Register;
    struct StatusRegister;
    struct StackPointer;
};