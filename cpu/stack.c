#include <xboy.h>
#include "cpu-internal.h"

/**
 * ld sp, n16
 * cycles: 3
 * bytes: 3
 */
void opcode_0x31(uint8_t opcode)
{
    reg_value(sp) = read_word_by_pc();
}
__register_opcode_table(0x31);

/**
 * ld [n16], sp
 * cycles: 5
 * bytes: 3
 */
void opcode_0x08(uint8_t opcode)
{
    uint16_t addr = read_word_by_pc();
    uint16_t sp = reg_value(sp);
    bus_write(addr, sp & 0xff);
    bus_write(addr + 1, (sp >> 8) & 0xff);
}
__register_opcode_table(0x08);

/**
 * ld hl, sp+e8
 * cycles: 3
 * bytes: 2
 */
void opcode_0xf8(uint8_t opcode)
{
    int8_t offset = read_byte_by_pc();
    uint16_t sp = reg_value(sp);
    uint16_t result = sp + offset;
    reg_value(hl) = result;

    reg_value(z_flag) = 0;
    reg_value(n_flag) = 0;
    reg_value(h_flag) = ((offset & 0xf) + (sp & 0xf) > (result & 0xf)) ? 1 : 0;
    reg_value(c_flag) = ((offset & 0xff) + (sp & 0xff) > (result & 0xff)) ? 1 : 0;
}
__register_opcode_table(0xf8);

/**
 * ld sp, hl
 * cycles: 2
 * bytes: 1
 */
void opcode_0xf9(uint8_t opcode)
{
    reg_value(sp) = reg_value(hl);
}
__register_opcode_table(0xf9);
