#include <xboy.h>
#include "cpu-internal.h"

static uint8_t execute_cb_instruction(uint8_t opcode_cb)
{
    opcode_fn fn = opcode_cb_table[opcode_cb];
    return fn(opcode_cb);
}

/**
 * NOP
 * cycles: 1
 * bytes: 1
 */
uint8_t opcode_0x00(uint8_t opcode)
{
    log_debug("opcode: %x", opcode);
    return cycles_table[opcode];
}
register_opcode_table(0x00);

/**
 * STOP n8
 * cycles: 1
 * bytes: 2
 */
uint8_t opcode_0x10(uint8_t opcode)
{
    read_byte_by_pc();
    // TODO: anything else?
    return cycles_table[opcode];
}
register_opcode_table(0x10);

/**
 * HALT
 * cycles: 1
 * bytes: 1
 */
uint8_t opcode_0x76(uint8_t opcode)
{
    cpu.halted = 1;
    return cycles_table[opcode];
}
register_opcode_table(0x76);

/**
 * PREFIX cb
 * cycles: 1
 * bytes: 1
 */
uint8_t opcode_0xcb(uint8_t opcode)
{
    uint8_t opcode_cb = read_byte_by_pc();
    return cycles_table[opcode] + execute_cb_instruction(opcode_cb);
}
register_opcode_table(0xcb);

/**
 * DI
 * cycles: 1
 * bytes: 1
 */
uint8_t opcode_0xf3(uint8_t opcode)
{
    cpu.interrupts.ime = 0;
    return cycles_table[opcode];
}
register_opcode_table(0xf3);

/**
 * EI
 * cycles: 1
 * bytes: 1
 */
uint8_t opcode_0xfb(uint8_t opcode)
{
    cpu.interrupts.ime = 1;
    return cycles_table[opcode];
}
register_opcode_table(0xfb);