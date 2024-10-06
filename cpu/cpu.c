#include <stdio.h>

#include <cpu.h>
#include <insts.h>

static struct Cpu cpu;

static struct Instruction *cpu_fetch_instruction()
{
    return parse_next_instruction(cpu.regs.pc);
}

static int cpu_execute_instruction(struct Instruction *inst)
{
    if (inst == NULL)
        return -1;

    return inst->execute(inst, &cpu);
}

static struct Cpu cpu = {
    .regs = {
        .a = 0,
        .b = 0,
        .c = 1,
        .d = 2,
        .e = 3,
        .h = 4,
        .l = 5,
        .pc = 0x100,
    },
};

int cpu_step()
{
    struct Instruction *inst = cpu_fetch_instruction();
    cpu_execute_instruction(inst);
    return 0;
}