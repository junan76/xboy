#include <xboy.h>
#include "cpu-internal.h"

void opcode_0x00(uint8_t opcode)
{
    log_debug("opcode: %x", opcode);
}

void misc_init()
{
    opcode_table[0x00] = opcode_0x00;
}