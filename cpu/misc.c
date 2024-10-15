#include <xboy.h>
#include "cpu-internal.h"

/**
 * NOP
 * cycles: 1
 * bytes: 1
 */
void opcode_0x00(uint8_t opcode)
{
    log_debug("opcode: %x", opcode);
}
register_opcode_table(0x00);