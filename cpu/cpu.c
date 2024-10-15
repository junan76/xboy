#include <xboy.h>
#include "cpu-internal.h"

uint8_t read_byte_by_pc()
{
    uint16_t *pc = reg(pc);
    uint8_t result = bus_read(*pc);
    *pc += 1;
    return result;
}

uint16_t read_word_by_pc()
{
    uint16_t result = 0;
    uint16_t *pc = reg(pc);

    result = bus_read(*pc + 1) << 8 | bus_read(*pc);
    *pc += 2;

    return result;
}

static void handle_interrupts()
{
}

static void execute_instruction(uint8_t opcode)
{
    opcode_fn fn = opcode_table[opcode];
    fn(opcode);
}

static void opcode_default(uint8_t opcode)
{
    log_err("unimplemented opcode: %x", opcode);
}

int cpu_step()
{

    handle_interrupts();

    uint8_t opcode = read_byte_by_pc();
    execute_instruction(opcode);
}

int cpu_init()
{
    /*Registers init.*/
    reg_value(pc) = 0x100;

    return 0;
}

struct CPU cpu;
opcode_fn opcode_table[256];