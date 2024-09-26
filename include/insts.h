#ifndef INSTS_H
#define INSTS_H

#include <stdint.h>

struct Instruction
{
    uint8_t opcode;
    void (*execute)(struct Cpu *cpu);
};

#endif