#include <stdio.h>

#include <insts.h>
#include <cpu.h>

#include "instructions.h"

static int exec_inst_nop(struct Instruction *inst, struct Cpu *cpu)
{
    printf("NOP executed\n");
    cpu->regs.pc++;
    return 0;
}
__register_instruction(0x00, nop, optype_none, optype_none, 4, exec_inst_nop);
