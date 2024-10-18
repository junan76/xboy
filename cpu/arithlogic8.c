#include <xboy.h>
#include "cpu-internal.h"

/**
 * ADC a, r8
 * cycles: 1
 * bytes: 1
 */
static uint8_t adc_a_r8(uint8_t opcode, uint8_t *rs)
{

    uint8_t carry = reg_value(c_flag);
    uint16_t result = reg_value(a) + *rs + carry;

    reg_value(z_flag) == (result & 0xff) == 0;
    reg_value(n_flag) = 0;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) + (*rs & 0x0f) + carry > 0x0f);
    reg_value(c_flag) = (result > 0xff);

    reg_value(a) = result & 0xff;

    return cycles_table[opcode];
}

#define declare_adc_a_r8(_opcode, _rs)       \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return adc_a_r8(opcode, reg(_rs));   \
    }                                        \
    register_opcode_table(_opcode);

declare_adc_a_r8(0x88, b);
declare_adc_a_r8(0x89, c);
declare_adc_a_r8(0x8a, d);
declare_adc_a_r8(0x8b, e);
declare_adc_a_r8(0x8c, h);
declare_adc_a_r8(0x8d, l);
declare_adc_a_r8(0x8f, a);

/**
 * ADC a, [hl]
 * cycles: 2
 * bytes: 1
 */
uint8_t opcode_0x8e(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    uint8_t carry = reg_value(c_flag);
    uint16_t result = reg_value(a) + value + carry;

    reg_value(z_flag) == (result & 0xff) == 0;
    reg_value(n_flag) = 0;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) + (value & 0x0f) + carry > 0x0f);
    reg_value(c_flag) = (result > 0xff);

    reg_value(a) = result & 0xff;

    return cycles_table[opcode];
}
register_opcode_table(0x8e);

/**
 * ADC a, n8
 * cycles: 2
 * bytes: 2
 */
uint8_t opcode_0xce(uint8_t opcode)
{
    uint8_t value = read_byte_by_pc();
    uint8_t carry = reg_value(c_flag);
    uint16_t result = reg_value(a) + value + carry;

    reg_value(z_flag) == (result & 0xff) == 0;
    reg_value(n_flag) = 0;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) + (value & 0x0f) + carry > 0x0f);
    reg_value(c_flag) = (result > 0xff);

    reg_value(a) = result & 0xff;
    return cycles_table[opcode];
}
register_opcode_table(0xce);

/**
 * ADD a, r8
 * cycles: 1
 * bytes: 1
 */
static uint8_t add_a_r8(uint8_t opcode, uint8_t *rs)
{
    uint16_t result = reg_value(a) + *rs;

    reg_value(z_flag) == (result & 0xff) == 0;
    reg_value(n_flag) = 0;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) + (*rs & 0x0f) > 0x0f);
    reg_value(c_flag) = (result > 0xff);

    reg_value(a) = result & 0xff;
    return cycles_table[opcode];
}

#define declare_add_a_r8(_opcode, _rs)       \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return add_a_r8(opcode, reg(_rs));   \
    }                                        \
    register_opcode_table(_opcode);

declare_add_a_r8(0x80, b);
declare_add_a_r8(0x81, c);
declare_add_a_r8(0x82, d);
declare_add_a_r8(0x83, e);
declare_add_a_r8(0x84, h);
declare_add_a_r8(0x85, l);
declare_add_a_r8(0x87, a);

/**
 * ADD a, [hl]
 * cycles: 2
 * bytes: 1
 */
uint8_t opcode_0x86(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    uint16_t result = reg_value(a) + value;

    reg_value(z_flag) == (result & 0xff) == 0;
    reg_value(n_flag) = 0;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) + (value & 0x0f) > 0x0f);
    reg_value(c_flag) = (result > 0xff);

    reg_value(a) = result & 0xff;
    return cycles_table[opcode];
}
register_opcode_table(0x86);

/**
 * ADD a, n8
 * cycles: 2
 * bytes: 2
 */
uint8_t opcode_0xc6(uint8_t opcode)
{
    uint8_t value = read_byte_by_pc();
    uint16_t result = reg_value(a) + value;

    reg_value(z_flag) == (result & 0xff) == 0;
    reg_value(n_flag) = 0;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) + (value & 0x0f) > 0x0f);
    reg_value(c_flag) = (result > 0xff);

    reg_value(a) = result & 0xff;
    return cycles_table[opcode];
}
register_opcode_table(0xc6);

/**
 * AND a, r8
 * cycles: 1
 * bytes: 1
 */
static uint8_t and_a_r8(uint8_t opcode, uint8_t *rs)
{
    reg_value(a) &= *rs;

    reg_value(z_flag) = (reg_value(a) == 0);
    reg_value(n_flag) = 0;
    reg_value(h_flag) = 1;
    reg_value(c_flag) = 0;

    return cycles_table[opcode];
}

#define declare_and_a_r8(_opcode, _rs)       \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return and_a_r8(opcode, reg(_rs));   \
    }                                        \
    register_opcode_table(_opcode);

declare_and_a_r8(0xa0, b);
declare_and_a_r8(0xa1, c);
declare_and_a_r8(0xa2, d);
declare_and_a_r8(0xa3, e);
declare_and_a_r8(0xa4, h);
declare_and_a_r8(0xa5, l);
declare_and_a_r8(0xa7, a);

/**
 * AND a, [hl]
 * cycles: 2
 * bytes: 1
 */
uint8_t opcode_0xa6(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    reg_value(a) &= value;

    reg_value(z_flag) = (reg_value(a) == 0);
    reg_value(n_flag) = 0;
    reg_value(h_flag) = 1;
    reg_value(c_flag) = 0;

    return cycles_table[opcode];
}
register_opcode_table(0xa6);

/**
 * AND a, n8
 * cycles: 2
 * bytes: 2
 */
uint8_t opcode_0xe6(uint8_t opcode)
{
    uint8_t value = read_byte_by_pc();
    reg_value(a) &= value;

    reg_value(z_flag) = (reg_value(a) == 0);
    reg_value(n_flag) = 0;
    reg_value(h_flag) = 1;
    reg_value(c_flag) = 0;

    return cycles_table[opcode];
}
register_opcode_table(0xe6);

/**
 * OR a, r8
 * cycles: 1
 * bytes: 1
 */
static uint8_t or_a_r8(uint8_t opcode, uint8_t *rs)
{
    reg_value(a) |= *rs;

    reg_value(z_flag) = (reg_value(a) == 0);
    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(c_flag) = 0;

    return cycles_table[opcode];
}

#define declare_or_a_r8(_opcode, _rs)        \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return or_a_r8(opcode, reg(_rs));    \
    }                                        \
    register_opcode_table(_opcode);

declare_or_a_r8(0xb0, b);
declare_or_a_r8(0xb1, c);
declare_or_a_r8(0xb2, d);
declare_or_a_r8(0xb3, e);
declare_or_a_r8(0xb4, h);
declare_or_a_r8(0xb5, l);
declare_or_a_r8(0xb7, a);

/**
 * OR a, [hl]
 * cycles: 2
 * bytes: 1
 */
uint8_t opcode_0xb6(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    reg_value(a) |= value;

    reg_value(z_flag) = (reg_value(a) == 0);
    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(c_flag) = 0;

    return cycles_table[opcode];
}
register_opcode_table(0xb6);

/**
 * OR a, n8
 * cycles: 2
 * bytes: 2
 */
uint8_t opcode_0xf6(uint8_t opcode)
{
    uint8_t value = read_byte_by_pc();
    reg_value(a) |= value;

    reg_value(z_flag) = (reg_value(a) == 0);
    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(c_flag) = 0;

    return cycles_table[opcode];
}
register_opcode_table(0xf6);

/**
 * XOR a, r8
 * cycles: 1
 * bytes: 1
 */
static uint8_t xor_a_r8(uint8_t opcode, uint8_t *rs)
{
    reg_value(a) ^= *rs;

    reg_value(z_flag) = (reg_value(a) == 0);
    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(c_flag) = 0;

    return cycles_table[opcode];
}

#define declare_xor_a_r8(_opcode, _rs)       \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return xor_a_r8(opcode, reg(_rs));   \
    }                                        \
    register_opcode_table(_opcode);

declare_xor_a_r8(0xa8, b);
declare_xor_a_r8(0xa9, c);
declare_xor_a_r8(0xaa, d);
declare_xor_a_r8(0xab, e);
declare_xor_a_r8(0xac, h);
declare_xor_a_r8(0xad, l);
declare_xor_a_r8(0xaf, a);

/**
 * XORR a, [hl]
 * cycles: 2
 * bytes: 1
 */
uint8_t opcode_0xae(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    reg_value(a) ^= value;

    reg_value(z_flag) = (reg_value(a) == 0);
    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(c_flag) = 0;

    return cycles_table[opcode];
}
register_opcode_table(0xae);

/**
 * XOR a, n8
 * cycles: 2
 * bytes: 2
 */
uint8_t opcode_0xee(uint8_t opcode)
{
    uint8_t value = read_byte_by_pc();
    reg_value(a) ^= value;

    reg_value(z_flag) = (reg_value(a) == 0);
    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(c_flag) = 0;

    return cycles_table[opcode];
}
register_opcode_table(0xee);

/**
 * CP a, r8
 * cycles: 1
 * bytes: 1
 */
static uint8_t cp_a_r8(uint8_t opcode, uint8_t *rs)
{
    reg_value(z_flag) = (reg_value(a) == *rs);
    reg_value(n_flag) = 1;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) < (*rs & 0x0f));
    reg_value(c_flag) = (reg_value(a) < *rs);

    return cycles_table[opcode];
}

#define declare_cp_a_r8(_opcode, _rs)        \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return cp_a_r8(opcode, reg(_rs));    \
    }                                        \
    register_opcode_table(_opcode);

declare_cp_a_r8(0xb8, b);
declare_cp_a_r8(0xb9, c);
declare_cp_a_r8(0xba, d);
declare_cp_a_r8(0xbb, e);
declare_cp_a_r8(0xbc, h);
declare_cp_a_r8(0xbd, l);
declare_cp_a_r8(0xbf, a);

/**
 * CP a, [hl]
 * cycles: 2
 * bytes: 1
 */
uint8_t opcode_0xbe(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    reg_value(z_flag) = (reg_value(a) == value);
    reg_value(n_flag) = 1;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) < (value & 0x0f));
    reg_value(c_flag) = (reg_value(a) < value);

    return cycles_table[opcode];
}
register_opcode_table(0xbe);

/**
 * CP a, n8
 * cycles: 2
 * bytes: 2
 */
uint8_t opcode_0xfe(uint8_t opcode)
{
    uint8_t value = read_byte_by_pc();
    reg_value(z_flag) = (reg_value(a) == value);
    reg_value(n_flag) = 1;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) < (value & 0x0f));
    reg_value(c_flag) = (reg_value(a) < value);

    return cycles_table[opcode];
}
register_opcode_table(0xfe);

/**
 * SUB a, r8
 * cycles: 1
 * bytes: 1
 */
static uint8_t sub_a_r8(uint8_t opcode, uint8_t *rs)
{
    uint8_t result = reg_value(a) - *rs;
    reg_value(z_flag) = (result == 0);
    reg_value(n_flag) = 1;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) < (*rs & 0x0f));
    reg_value(c_flag) = (reg_value(a) < *rs);
    reg_value(a) = result;

    return cycles_table[opcode];
}

#define declare_sub_a_r8(_opcode, _rs)       \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return sub_a_r8(opcode, reg(_rs));   \
    }                                        \
    register_opcode_table(_opcode);

declare_sub_a_r8(0x90, b);
declare_sub_a_r8(0x91, c);
declare_sub_a_r8(0x92, d);
declare_sub_a_r8(0x93, e);
declare_sub_a_r8(0x94, h);
declare_sub_a_r8(0x95, l);
declare_sub_a_r8(0x97, a);

/**
 * SUB a, [hl]
 * cycles: 2
 * bytes: 1
 */
uint8_t opcode_0x96(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    uint8_t result = reg_value(a) - value;
    reg_value(z_flag) = (result == 0);
    reg_value(n_flag) = 1;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) < (value & 0x0f));
    reg_value(c_flag) = (reg_value(a) < value);
    reg_value(a) = result;

    return cycles_table[opcode];
}
register_opcode_table(0x96);

/**
 * SUB a, n8
 * cycles: 2
 * bytes: 2
 */
uint8_t opcode_0xd6(uint8_t opcode)
{
    uint8_t value = read_byte_by_pc();
    uint8_t result = reg_value(a) - value;
    reg_value(z_flag) = (result == 0);
    reg_value(n_flag) = 1;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) < (value & 0x0f));
    reg_value(c_flag) = (reg_value(a) < value);
    reg_value(a) = result;

    return cycles_table[opcode];
}
register_opcode_table(0xd6);

/**
 * SUBC a, r8
 * cycles: 1
 * bytes: 1
 */
static uint8_t sbc_a_r8(uint8_t opcode, uint8_t *rs)
{
    uint8_t carry = reg_value(c_flag);
    uint8_t result = reg_value(a) - *rs - carry;
    reg_value(z_flag) = (result == 0);
    reg_value(n_flag) = 1;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) < (*rs & 0x0f) + carry);
    reg_value(c_flag) = (reg_value(a) < *rs + carry);
    reg_value(a) = result;

    return cycles_table[opcode];
}

#define declare_sbc_a_r8(_opcode, _rs)       \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return sbc_a_r8(opcode, reg(_rs));   \
    }                                        \
    register_opcode_table(_opcode);

declare_sbc_a_r8(0x98, b);
declare_sbc_a_r8(0x99, c);
declare_sbc_a_r8(0x9a, d);
declare_sbc_a_r8(0x9b, e);
declare_sbc_a_r8(0x9c, h);
declare_sbc_a_r8(0x9d, l);
declare_sbc_a_r8(0x9f, a);

/**
 * SUBC a, [hl]
 * cycles: 2
 * bytes: 1
 */
uint8_t opcode_0x9e(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    uint8_t carry = reg_value(c_flag);
    uint8_t result = reg_value(a) - value - carry;
    reg_value(z_flag) = (result == 0);
    reg_value(n_flag) = 1;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) < (value & 0x0f) + carry);
    reg_value(c_flag) = (reg_value(a) < value + carry);
    reg_value(a) = result;

    return cycles_table[opcode];
}
register_opcode_table(0x9e);

/**
 * SUBC a, n8
 * cycles: 2
 * bytes: 2
 */
uint8_t opcode_0xde(uint8_t opcode)
{
    uint8_t value = read_byte_by_pc();
    uint8_t carry = reg_value(c_flag);
    uint8_t result = reg_value(a) - value - carry;
    reg_value(z_flag) = (result == 0);
    reg_value(n_flag) = 1;
    reg_value(h_flag) = ((reg_value(a) & 0x0f) < (value & 0x0f) + carry);
    reg_value(c_flag) = (reg_value(a) < value + carry);
    reg_value(a) = result;

    return cycles_table[opcode];
}
register_opcode_table(0xde);

/**
 * INC r8
 * cycles: 1
 * bytes: 1
 */
static uint8_t inc_r8(uint8_t opcode, uint8_t *rs)
{
    uint8_t result = *rs + 1;
    reg_value(z_flag) = (result == 0);
    reg_value(n_flag) = 0;
    reg_value(h_flag) = ((*rs & 0x0f) == 0x0f);
    *rs = result;

    return cycles_table[opcode];
}

#define declare_inc_r8(_opcode, _rs)         \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return inc_r8(opcode, reg(_rs));     \
    }                                        \
    register_opcode_table(_opcode);

declare_inc_r8(0x04, b);
declare_inc_r8(0x0c, c);
declare_inc_r8(0x14, d);
declare_inc_r8(0x1c, e);
declare_inc_r8(0x24, h);
declare_inc_r8(0x2c, l);
declare_inc_r8(0x3c, a);

/**
 * INC [hl]
 * cycles: 3
 * bytes: 1
 */
uint8_t opcode_0x34(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    uint8_t result = value + 1;
    bus_write(reg_value(hl), result);
    reg_value(z_flag) = (result == 0);
    reg_value(n_flag) = 0;
    reg_value(h_flag) = ((value & 0x0f) == 0x0f);

    return cycles_table[opcode];
}
register_opcode_table(0x34);

/**
 * DEC r8
 * cycles: 1
 * bytes: 1
 */
static uint8_t dec_r8(uint8_t opcode, uint8_t *rs)
{
    uint8_t result = *rs - 1;
    reg_value(z_flag) = (result == 0);
    reg_value(n_flag) = 1;
    reg_value(h_flag) = ((*rs & 0x0f) == 0);
    *rs = result;

    return cycles_table[opcode];
}

#define declare_dec_r8(_opcode, _rs)         \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return dec_r8(opcode, reg(_rs));     \
    }                                        \
    register_opcode_table(_opcode);

declare_dec_r8(0x05, b);
declare_dec_r8(0x0d, c);
declare_dec_r8(0x15, d);
declare_dec_r8(0x1d, e);
declare_dec_r8(0x25, h);
declare_dec_r8(0x2d, l);
declare_dec_r8(0x3d, a);

/**
 * DEC [hl]
 * cycles: 3
 * bytes: 1
 */
uint8_t opcode_0x35(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    uint8_t result = value - 1;
    bus_write(reg_value(hl), result);
    reg_value(z_flag) = (result == 0);
    reg_value(n_flag) = 1;
    reg_value(h_flag) = ((value & 0x0f) == 0);

    return cycles_table[opcode];
}
register_opcode_table(0x35);

/**
 * CPL
 * cycles: 1
 * bytes: 1
 */
uint8_t opcode_0x2f(uint8_t opcode)
{
    reg_value(a) = ~reg_value(a);
    reg_value(n_flag) = 1;
    reg_value(h_flag) = 1;

    return cycles_table[opcode];
}
register_opcode_table(0x2f);

/**
 * CCF
 * cycles: 1
 * bytes: 1
 */
uint8_t opcode_0x3f(uint8_t opcode)
{
    reg_value(c_flag) = !reg_value(c_flag);
    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;

    return cycles_table[opcode];
}
register_opcode_table(0x3f);

/**
 * SCF
 * cycles: 1
 * bytes: 1
 */
uint8_t opcode_0x37(uint8_t opcode)
{
    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(c_flag) = 1;
    return cycles_table[opcode];
}

// TODO: DAA