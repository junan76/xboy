#include <xboy.h>
#include "cpu-internal.h"

/**
 * LD r16, n16
 * cycles: 3
 * bytes: 3
 */
static void ld_r16n16(uint8_t opcode, uint16_t *rd)
{
    *rd = read_word_by_pc();
}

#define declare_ld_r16n16(_opcode, _rd)   \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        ld_r16n16(opcode, reg(_rd));      \
    }                                     \
    register_opcode_table(_opcode)

declare_ld_r16n16(0x01, bc);
declare_ld_r16n16(0x11, de);
declare_ld_r16n16(0x21, hl);
declare_ld_r16n16(0x31, hl);

/**
 * LD [n16], sp
 * cycles: 5
 * bytes: 3
 */
static void ld_memn16_sp(uint8_t opcode)
{
    uint16_t addr = read_word_by_pc();
    uint16_t sp = reg_value(sp);
    bus_write(addr, sp & 0xff);
    bus_write(addr + 1, (sp >> 8) & 0xff);
}

void opcode_0x08(uint8_t opcode)
{
    ld_memn16_sp(opcode);
}
register_opcode_table(0x08);

/**
 * POP r16
 * cycles: 3
 * bytes: 1
 */
static void pop_r16(uint8_t opcode, uint16_t *rd)
{
    *rd = 0;
    *rd |= bus_read(reg_value(sp)++);
    *rd |= bus_read(reg_value(sp)++) << 8;
}

#define declare_pop_r16(_opcode, _rd)     \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        pop_r16(opcode, reg(_rd));        \
    }                                     \
    register_opcode_table(_opcode);

declare_pop_r16(0xc1, bc);
declare_pop_r16(0xd1, de);
declare_pop_r16(0xe1, hl);
declare_pop_r16(0xf1, af);

/**
 * PUSH r16
 * cycles: 4
 * bytes: 1
 */
static void push_r16(uint8_t opcode, uint16_t *rs)
{
    uint16_t value = *rs;
    bus_write(--reg_value(sp), (value >> 8) & 0xff);
    bus_write(--reg_value(sp), value & 0xff);
}

#define declare_push_r16(_opcode, _rd)    \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        push_r16(opcode, reg(_rd));       \
    }                                     \
    register_opcode_table(_opcode);

declare_push_r16(0xc5, bc);
declare_push_r16(0xd5, de);
declare_push_r16(0xe5, hl);
declare_push_r16(0xf5, af);

/**
 * LD hl, sp+e8
 * cycles: 3
 * bytes: 2
 */
static void ld_hl_spe8(uint8_t opcode)
{
    int8_t offset = read_byte_by_pc();
    uint16_t sp = reg_value(sp);
    reg_value(hl) = sp + offset;

    reg_value(z_flag) = 0;
    reg_value(n_flag) = 0;
    reg_value(h_flag) = carry_on_bit(3, sp, offset);
    reg_value(c_flag) = carry_on_bit(7, sp, offset);
}

void opcode_0xf8(uint8_t opcode)
{
    ld_hl_spe8(opcode);
}
register_opcode_table(0xf8);

/**
 * LD sp, hl
 * cycles: 2
 * bytes: 1
 */
static void ld_sp_hl(uint8_t opcode)
{
    reg_value(sp) = reg_value(hl);
}

void opcode_0xf9(uint8_t opcode)
{
    ld_sp_hl(opcode);
}
register_opcode_table(0xf9);