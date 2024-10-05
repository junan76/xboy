#ifndef INSTS_H
#define INSTS_H

#include <stdint.h>

struct Cpu;

enum OperandType
{
    optype_r8_b,
    optype_r8_c,
    optype_r8_d,
    optype_r8_e,
    optype_r8_h,
    optype_r8_l,
    optype_r8_a,
    optype_r16_bc,
    optype_r16_de,
    optype_r16_hl,
    optype_r16_sp,
    optype_16mem_bc,
    optype_16mem_de,
    optype_16mem_hl,
    optype_imm8,
    optype_imm16,
    optype_none,
};

struct Instruction
{
    uint8_t opcode;
    enum OperandType op1;
    enum OperandType op2;
    uint8_t n_cycles;
    int (*execute)(struct Instruction *inst, struct Cpu *cpu);
};

struct Instruction *parse_next_instruction(uint16_t pc);

#endif