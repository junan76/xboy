#include <stdio.h>

#include <cpu.h>
#include <insts.h>
#include "instructions.h"

static const char *reg8_name_from_optype(enum OperandType optype)
{
    switch (optype)
    {
    case optype_r8_b:
        return "B";
    case optype_r8_c:
        return "C";
    case optype_r8_d:
        return "D";
    case optype_r8_e:
        return "E";
    case optype_r8_h:
        return "H";
    case optype_r8_l:
        return "L";
    case optype_r8_a:
        return "A";
    default:
        return "unknown reg8";
    }
}

static uint8_t *reg8_from_optype(enum OperandType optype, struct Cpu *cpu)
{

    uint8_t *r8 = NULL;

    switch (optype)
    {
    case optype_r8_b:
        r8 = &cpu->regs.b;
        break;
    case optype_r8_c:
        r8 = &cpu->regs.c;
        break;
    case optype_r8_d:
        r8 = &cpu->regs.d;
        break;
    case optype_r8_e:
        r8 = &cpu->regs.e;
        break;
    case optype_r8_h:
        r8 = &cpu->regs.h;
        break;
    case optype_r8_l:
        r8 = &cpu->regs.l;
        break;
    case optype_r8_a:
        r8 = &cpu->regs.a;
        break;
    default:
        printf("%s: invalid op1 type: %d\n", optype);
        break;
    }

    return r8;
}

static int exec_inst_ld_r8_r8(struct Instruction *inst, struct Cpu *cpu)
{
    uint8_t *rd;
    uint8_t *rs;

    rd = reg8_from_optype(inst->op1, cpu);
    rs = reg8_from_optype(inst->op2, cpu);

    if (rd == NULL || rs == NULL)
        return -1;

    *rd = *rs;
    cpu->regs.pc++;
    printf("Instruction: ld %s, %s\n", reg8_name_from_optype(inst->op1), reg8_name_from_optype(inst->op2));

    return 0;
}

/*ld c, r8*/
__register_instruction(0x40, ld, optype_r8_b, optype_r8_b, 4, exec_inst_ld_r8_r8);
__register_instruction(0x41, ld, optype_r8_b, optype_r8_c, 4, exec_inst_ld_r8_r8);
__register_instruction(0x42, ld, optype_r8_b, optype_r8_d, 4, exec_inst_ld_r8_r8);
__register_instruction(0x43, ld, optype_r8_b, optype_r8_e, 4, exec_inst_ld_r8_r8);
__register_instruction(0x44, ld, optype_r8_b, optype_r8_h, 4, exec_inst_ld_r8_r8);
__register_instruction(0x45, ld, optype_r8_b, optype_r8_l, 4, exec_inst_ld_r8_r8);
__register_instruction(0x47, ld, optype_r8_b, optype_r8_a, 4, exec_inst_ld_r8_r8);

/*ld c, r8*/
__register_instruction(0x48, ld, optype_r8_c, optype_r8_b, 4, exec_inst_ld_r8_r8);
__register_instruction(0x49, ld, optype_r8_c, optype_r8_c, 4, exec_inst_ld_r8_r8);
__register_instruction(0x4a, ld, optype_r8_c, optype_r8_d, 4, exec_inst_ld_r8_r8);
__register_instruction(0x4b, ld, optype_r8_c, optype_r8_e, 4, exec_inst_ld_r8_r8);
__register_instruction(0x4c, ld, optype_r8_c, optype_r8_h, 4, exec_inst_ld_r8_r8);
__register_instruction(0x4d, ld, optype_r8_c, optype_r8_l, 4, exec_inst_ld_r8_r8);
__register_instruction(0x4f, ld, optype_r8_c, optype_r8_a, 4, exec_inst_ld_r8_r8);

/*ld d, r8*/
__register_instruction(0x50, ld, optype_r8_d, optype_r8_b, 4, exec_inst_ld_r8_r8);
__register_instruction(0x51, ld, optype_r8_d, optype_r8_c, 4, exec_inst_ld_r8_r8);
__register_instruction(0x52, ld, optype_r8_d, optype_r8_d, 4, exec_inst_ld_r8_r8);
__register_instruction(0x53, ld, optype_r8_d, optype_r8_e, 4, exec_inst_ld_r8_r8);
__register_instruction(0x54, ld, optype_r8_d, optype_r8_h, 4, exec_inst_ld_r8_r8);
__register_instruction(0x55, ld, optype_r8_d, optype_r8_l, 4, exec_inst_ld_r8_r8);
__register_instruction(0x57, ld, optype_r8_d, optype_r8_a, 4, exec_inst_ld_r8_r8);

/*ld e, r8*/
__register_instruction(0x58, ld, optype_r8_e, optype_r8_b, 4, exec_inst_ld_r8_r8);
__register_instruction(0x59, ld, optype_r8_e, optype_r8_c, 4, exec_inst_ld_r8_r8);
__register_instruction(0x5a, ld, optype_r8_e, optype_r8_d, 4, exec_inst_ld_r8_r8);
__register_instruction(0x5b, ld, optype_r8_e, optype_r8_e, 4, exec_inst_ld_r8_r8);
__register_instruction(0x5c, ld, optype_r8_e, optype_r8_h, 4, exec_inst_ld_r8_r8);
__register_instruction(0x5d, ld, optype_r8_e, optype_r8_l, 4, exec_inst_ld_r8_r8);
__register_instruction(0x5f, ld, optype_r8_e, optype_r8_a, 4, exec_inst_ld_r8_r8);

/*ld h, r8*/
__register_instruction(0x60, ld, optype_r8_h, optype_r8_b, 4, exec_inst_ld_r8_r8);
__register_instruction(0x61, ld, optype_r8_h, optype_r8_c, 4, exec_inst_ld_r8_r8);
__register_instruction(0x62, ld, optype_r8_h, optype_r8_d, 4, exec_inst_ld_r8_r8);
__register_instruction(0x63, ld, optype_r8_h, optype_r8_e, 4, exec_inst_ld_r8_r8);
__register_instruction(0x64, ld, optype_r8_h, optype_r8_h, 4, exec_inst_ld_r8_r8);
__register_instruction(0x65, ld, optype_r8_h, optype_r8_l, 4, exec_inst_ld_r8_r8);
__register_instruction(0x67, ld, optype_r8_h, optype_r8_a, 4, exec_inst_ld_r8_r8);

/*ld l, r8*/
__register_instruction(0x68, ld, optype_r8_l, optype_r8_b, 4, exec_inst_ld_r8_r8);
__register_instruction(0x69, ld, optype_r8_l, optype_r8_c, 4, exec_inst_ld_r8_r8);
__register_instruction(0x6a, ld, optype_r8_l, optype_r8_d, 4, exec_inst_ld_r8_r8);
__register_instruction(0x6b, ld, optype_r8_l, optype_r8_e, 4, exec_inst_ld_r8_r8);
__register_instruction(0x6c, ld, optype_r8_l, optype_r8_h, 4, exec_inst_ld_r8_r8);
__register_instruction(0x6d, ld, optype_r8_l, optype_r8_l, 4, exec_inst_ld_r8_r8);
__register_instruction(0x6f, ld, optype_r8_l, optype_r8_a, 4, exec_inst_ld_r8_r8);

/*ld a, r8*/
__register_instruction(0x78, ld, optype_r8_a, optype_r8_b, 4, exec_inst_ld_r8_r8);
__register_instruction(0x79, ld, optype_r8_a, optype_r8_c, 4, exec_inst_ld_r8_r8);
__register_instruction(0x7a, ld, optype_r8_a, optype_r8_d, 4, exec_inst_ld_r8_r8);
__register_instruction(0x7b, ld, optype_r8_a, optype_r8_e, 4, exec_inst_ld_r8_r8);
__register_instruction(0x7c, ld, optype_r8_a, optype_r8_h, 4, exec_inst_ld_r8_r8);
__register_instruction(0x7d, ld, optype_r8_a, optype_r8_l, 4, exec_inst_ld_r8_r8);
__register_instruction(0x7f, ld, optype_r8_a, optype_r8_a, 4, exec_inst_ld_r8_r8);