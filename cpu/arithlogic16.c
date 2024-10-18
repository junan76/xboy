#include <xboy.h>
#include "cpu-internal.h"

/**
 * ADD hl, r16
 * cycles: 2
 * bytes: 1
 */
static uint8_t add_hl_r16(uint8_t opcode, uint16_t *rs)
{
    reg_value(n_flag) = 0;
    reg_value(h_flag) = carry_on_bit(11, reg_value(hl), *rs);
    reg_value(c_flag) = carry_on_bit(15, reg_value(hl), *rs);

    reg_value(hl) += *rs;
    return cycles_table[opcode];
}

#define declare_add_hl_r16(_opcode, _rs)     \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return add_hl_r16(opcode, reg(_rs)); \
    }                                        \
    register_opcode_table(_opcode)

declare_add_hl_r16(0x09, bc);
declare_add_hl_r16(0x19, de);
declare_add_hl_r16(0x29, hl);
declare_add_hl_r16(0x39, sp);

/**
 * INC r16
 * cycles: 2
 * bytes: 1
 */
static uint8_t inc_r16(uint8_t opcode, uint16_t *rd)
{
    *rd += 1;
    return cycles_table[opcode];
}

#define declare_inc_r16(_opcode, _rd)        \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return inc_r16(opcode, reg(_rd));    \
    }                                        \
    register_opcode_table(_opcode);

declare_inc_r16(0x03, bc);
declare_inc_r16(0x13, de);
declare_inc_r16(0x23, hl);
declare_inc_r16(0x33, sp);

/**
 * DEC r16
 * cycles: 2
 * bytes: 1
 */
static uint8_t dec_r16(uint8_t opcode, uint16_t *rd)
{
    *rd -= 1;
    return cycles_table[opcode];
}

#define declare_dec_r16(_opcode, _rd)        \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return dec_r16(opcode, reg(_rd));    \
    }                                        \
    register_opcode_table(_opcode);

declare_dec_r16(0x0b, bc);
declare_dec_r16(0x1b, de);
declare_dec_r16(0x2b, hl);
declare_dec_r16(0x3b, sp);

/**
 * ADD sp, e8
 * cycles: 4
 * bytes: 2
 */
uint8_t opcode_0xe8(uint8_t opcode)
{
    int8_t offset = read_byte_by_pc();
    uint16_t result = reg_value(sp) + offset;

    reg_value(z_flag) = 0;
    reg_value(n_flag) = 0;
    reg_value(h_flag) = carry_on_bit(3, reg_value(sp), offset);
    reg_value(c_flag) = carry_on_bit(7, reg_value(sp), offset);

    return cycles_table[opcode];
}
register_opcode_table(0xe8);