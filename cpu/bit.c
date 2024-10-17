#include <xboy.h>
#include "cpu-internal.h"

/**
 * BIT u3, r8
 * cycles: 2
 * bytes: 2(0xcb included)
 */
static uint8_t bit_u3_r8(uint8_t opcode, uint8_t *rs, uint8_t bit)
{
    reg_value(n_flag) = 0;
    reg_value(h_flag) = 1;

    if (((1 << bit) & *rs) == 0)
        reg_value(z_flag) = 1;
    else
        reg_value(z_flag) = 0;

    return cycles_cb_table[opcode];
}

#define declare_bit_u3_r8(_opcode, _rs, _bit)     \
    uint8_t opcode_cb_##_opcode(uint8_t opcode)   \
    {                                             \
        return bit_u3_r8(opcode, reg(_rs), _bit); \
    }                                             \
    register_opcode_cb_table(_opcode);

declare_bit_u3_r8(0x40, b, 0);
declare_bit_u3_r8(0x48, b, 1);
declare_bit_u3_r8(0x50, b, 2);
declare_bit_u3_r8(0x58, b, 3);
declare_bit_u3_r8(0x60, b, 4);
declare_bit_u3_r8(0x68, b, 5);
declare_bit_u3_r8(0x70, b, 6);
declare_bit_u3_r8(0x78, b, 7);

declare_bit_u3_r8(0x41, c, 0);
declare_bit_u3_r8(0x49, c, 1);
declare_bit_u3_r8(0x51, c, 2);
declare_bit_u3_r8(0x59, c, 3);
declare_bit_u3_r8(0x61, c, 4);
declare_bit_u3_r8(0x69, c, 5);
declare_bit_u3_r8(0x71, c, 6);
declare_bit_u3_r8(0x79, c, 7);

declare_bit_u3_r8(0x42, d, 0);
declare_bit_u3_r8(0x4a, d, 1);
declare_bit_u3_r8(0x52, d, 2);
declare_bit_u3_r8(0x5a, d, 3);
declare_bit_u3_r8(0x62, d, 4);
declare_bit_u3_r8(0x6a, d, 5);
declare_bit_u3_r8(0x72, d, 6);
declare_bit_u3_r8(0x7a, d, 7);

declare_bit_u3_r8(0x43, e, 0);
declare_bit_u3_r8(0x4b, e, 1);
declare_bit_u3_r8(0x53, e, 2);
declare_bit_u3_r8(0x5b, e, 3);
declare_bit_u3_r8(0x63, e, 4);
declare_bit_u3_r8(0x6b, e, 5);
declare_bit_u3_r8(0x73, e, 6);
declare_bit_u3_r8(0x7b, e, 7);

declare_bit_u3_r8(0x44, h, 0);
declare_bit_u3_r8(0x4c, h, 1);
declare_bit_u3_r8(0x54, h, 2);
declare_bit_u3_r8(0x5c, h, 3);
declare_bit_u3_r8(0x64, h, 4);
declare_bit_u3_r8(0x6c, h, 5);
declare_bit_u3_r8(0x74, h, 6);
declare_bit_u3_r8(0x7c, h, 7);

declare_bit_u3_r8(0x45, l, 0);
declare_bit_u3_r8(0x4d, l, 1);
declare_bit_u3_r8(0x55, l, 2);
declare_bit_u3_r8(0x5d, l, 3);
declare_bit_u3_r8(0x65, l, 4);
declare_bit_u3_r8(0x6d, l, 5);
declare_bit_u3_r8(0x75, l, 6);
declare_bit_u3_r8(0x7d, l, 7);

declare_bit_u3_r8(0x47, a, 0);
declare_bit_u3_r8(0x4f, a, 1);
declare_bit_u3_r8(0x57, a, 2);
declare_bit_u3_r8(0x5f, a, 3);
declare_bit_u3_r8(0x67, a, 4);
declare_bit_u3_r8(0x6f, a, 5);
declare_bit_u3_r8(0x77, a, 6);
declare_bit_u3_r8(0x7f, a, 7);

/**
 * BIT u3, [hl]
 * cycles: 3
 * bytes: 2(0xcb included)
 */
static uint8_t bit_u3_memhl(uint8_t opcode, uint8_t bit)
{
    uint8_t value = bus_read(reg_value(hl));

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 1;

    if (((1 << bit) & value) == 0)
        reg_value(z_flag) = 1;
    else
        reg_value(z_flag) = 0;

    return cycles_cb_table[opcode];
}

#define declare_bit_u3_memhl(_opcode, _bit)     \
    uint8_t opcode_cb_##_opcode(uint8_t opcode) \
    {                                           \
        return bit_u3_memhl(opcode, _bit);      \
    }                                           \
    register_opcode_cb_table(_opcode);

declare_bit_u3_memhl(0x46, 0);
declare_bit_u3_memhl(0x4e, 1);
declare_bit_u3_memhl(0x56, 2);
declare_bit_u3_memhl(0x5e, 3);
declare_bit_u3_memhl(0x66, 4);
declare_bit_u3_memhl(0x6e, 5);
declare_bit_u3_memhl(0x76, 6);
declare_bit_u3_memhl(0x7e, 7);

/**
 * RES u3, r8
 * cycles: 2
 * bytes: 2(0xcb included)
 */
static uint8_t res_u3_r8(uint8_t opcode, uint8_t *rd, uint8_t bit)
{
    *rd &= ~(1 << bit);
    return cycles_cb_table[opcode];
}

#define declare_res_u3_r8(_opcode, _rd, _bit)     \
    uint8_t opcode_cb_##_opcode(uint8_t opcode)   \
    {                                             \
        return res_u3_r8(opcode, reg(_rd), _bit); \
    }                                             \
    register_opcode_cb_table(_opcode);

declare_res_u3_r8(0x80, b, 0);
declare_res_u3_r8(0x88, b, 1);
declare_res_u3_r8(0x90, b, 2);
declare_res_u3_r8(0x98, b, 3);
declare_res_u3_r8(0xa0, b, 4);
declare_res_u3_r8(0xa8, b, 5);
declare_res_u3_r8(0xb0, b, 6);
declare_res_u3_r8(0xb8, b, 7);

declare_res_u3_r8(0x81, c, 0);
declare_res_u3_r8(0x89, c, 1);
declare_res_u3_r8(0x91, c, 2);
declare_res_u3_r8(0x99, c, 3);
declare_res_u3_r8(0xa1, c, 4);
declare_res_u3_r8(0xa9, c, 5);
declare_res_u3_r8(0xb1, c, 6);
declare_res_u3_r8(0xb9, c, 7);

declare_res_u3_r8(0x82, d, 0);
declare_res_u3_r8(0x8a, d, 1);
declare_res_u3_r8(0x92, d, 2);
declare_res_u3_r8(0x9a, d, 3);
declare_res_u3_r8(0xa2, d, 4);
declare_res_u3_r8(0xaa, d, 5);
declare_res_u3_r8(0xb2, d, 6);
declare_res_u3_r8(0xba, d, 7);

declare_res_u3_r8(0x83, e, 0);
declare_res_u3_r8(0x8b, e, 1);
declare_res_u3_r8(0x93, e, 2);
declare_res_u3_r8(0x9b, e, 3);
declare_res_u3_r8(0xa3, e, 4);
declare_res_u3_r8(0xab, e, 5);
declare_res_u3_r8(0xb3, e, 6);
declare_res_u3_r8(0xbb, e, 7);

declare_res_u3_r8(0x84, h, 0);
declare_res_u3_r8(0x8c, h, 1);
declare_res_u3_r8(0x94, h, 2);
declare_res_u3_r8(0x9c, h, 3);
declare_res_u3_r8(0xa4, h, 4);
declare_res_u3_r8(0xac, h, 5);
declare_res_u3_r8(0xb4, h, 6);
declare_res_u3_r8(0xbc, h, 7);

declare_res_u3_r8(0x85, l, 0);
declare_res_u3_r8(0x8d, l, 1);
declare_res_u3_r8(0x95, l, 2);
declare_res_u3_r8(0x9d, l, 3);
declare_res_u3_r8(0xa5, l, 4);
declare_res_u3_r8(0xad, l, 5);
declare_res_u3_r8(0xb5, l, 6);
declare_res_u3_r8(0xbd, l, 7);

declare_res_u3_r8(0x87, a, 0);
declare_res_u3_r8(0x8f, a, 1);
declare_res_u3_r8(0x97, a, 2);
declare_res_u3_r8(0x9f, a, 3);
declare_res_u3_r8(0xa7, a, 4);
declare_res_u3_r8(0xaf, a, 5);
declare_res_u3_r8(0xb7, a, 6);
declare_res_u3_r8(0xbf, a, 7);

/**
 * RES u3, [hl]
 * cycles: 4
 * bytes: 2(0xcb included)
 */
static uint8_t res_u3_memhl(uint8_t opcode, uint8_t bit)
{
    uint8_t value = bus_read(reg_value(hl));
    value &= ~(1 << bit);
    bus_write(reg_value(hl), value);
    return cycles_cb_table[opcode];
}

#define declare_res_u3_memhl(_opcode, _bit)     \
    uint8_t opcode_cb_##_opcode(uint8_t opcode) \
    {                                           \
        return res_u3_memhl(opcode, _bit);      \
    }                                           \
    register_opcode_cb_table(_opcode);

declare_res_u3_memhl(0x86, 0);
declare_res_u3_memhl(0x8e, 1);
declare_res_u3_memhl(0x96, 2);
declare_res_u3_memhl(0x9e, 3);
declare_res_u3_memhl(0xa6, 4);
declare_res_u3_memhl(0xae, 5);
declare_res_u3_memhl(0xb6, 6);
declare_res_u3_memhl(0xbe, 7);

/**
 * SET u3, r8
 * cycles: 2
 * bytes: 2(0xcb included)
 */
static uint8_t set_u3_r8(uint8_t opcode, uint8_t *rd, uint8_t bit)
{
    *rd |= (1 << bit);
    return cycles_cb_table[opcode];
}

#define declare_set_u3_r8(_opcode, _rd, _bit)     \
    uint8_t opcode_cb_##_opcode(uint8_t opcode)   \
    {                                             \
        return set_u3_r8(opcode, reg(_rd), _bit); \
    }                                             \
    register_opcode_cb_table(_opcode);

declare_set_u3_r8(0xc0, b, 0);
declare_set_u3_r8(0xc8, b, 1);
declare_set_u3_r8(0xd0, b, 2);
declare_set_u3_r8(0xd8, b, 3);
declare_set_u3_r8(0xe0, b, 4);
declare_set_u3_r8(0xe8, b, 5);
declare_set_u3_r8(0xf0, b, 6);
declare_set_u3_r8(0xf8, b, 7);

declare_set_u3_r8(0xc1, c, 0);
declare_set_u3_r8(0xc9, c, 1);
declare_set_u3_r8(0xd1, c, 2);
declare_set_u3_r8(0xd9, c, 3);
declare_set_u3_r8(0xe1, c, 4);
declare_set_u3_r8(0xe9, c, 5);
declare_set_u3_r8(0xf1, c, 6);
declare_set_u3_r8(0xf9, c, 7);

declare_set_u3_r8(0xc2, d, 0);
declare_set_u3_r8(0xca, d, 1);
declare_set_u3_r8(0xd2, d, 2);
declare_set_u3_r8(0xda, d, 3);
declare_set_u3_r8(0xe2, d, 4);
declare_set_u3_r8(0xea, d, 5);
declare_set_u3_r8(0xf2, d, 6);
declare_set_u3_r8(0xfa, d, 7);

declare_set_u3_r8(0xc3, e, 0);
declare_set_u3_r8(0xcb, e, 1);
declare_set_u3_r8(0xd3, e, 2);
declare_set_u3_r8(0xdb, e, 3);
declare_set_u3_r8(0xe3, e, 4);
declare_set_u3_r8(0xeb, e, 5);
declare_set_u3_r8(0xf3, e, 6);
declare_set_u3_r8(0xfb, e, 7);

declare_set_u3_r8(0xc4, h, 0);
declare_set_u3_r8(0xcc, h, 1);
declare_set_u3_r8(0xd4, h, 2);
declare_set_u3_r8(0xdc, h, 3);
declare_set_u3_r8(0xe4, h, 4);
declare_set_u3_r8(0xec, h, 5);
declare_set_u3_r8(0xf4, h, 6);
declare_set_u3_r8(0xfc, h, 7);

declare_set_u3_r8(0xc5, l, 0);
declare_set_u3_r8(0xcd, l, 1);
declare_set_u3_r8(0xd5, l, 2);
declare_set_u3_r8(0xdd, l, 3);
declare_set_u3_r8(0xe5, l, 4);
declare_set_u3_r8(0xed, l, 5);
declare_set_u3_r8(0xf5, l, 6);
declare_set_u3_r8(0xfd, l, 7);

declare_set_u3_r8(0xc7, a, 0);
declare_set_u3_r8(0xcf, a, 1);
declare_set_u3_r8(0xd7, a, 2);
declare_set_u3_r8(0xdf, a, 3);
declare_set_u3_r8(0xe7, a, 4);
declare_set_u3_r8(0xef, a, 5);
declare_set_u3_r8(0xf7, a, 6);
declare_set_u3_r8(0xff, a, 7);

/**
 * SET u3, [hl]
 * cycles: 4
 * bytes: 2(0xcb included)
 */
static uint8_t set_u3_memhl(uint8_t opcode, uint8_t bit)
{
    uint8_t value = bus_read(reg_value(hl));
    value |= (1 << bit);
    bus_write(reg_value(hl), value);
    return cycles_cb_table[opcode];
}

#define declare_set_u3_memhl(_opcode, _bit)     \
    uint8_t opcode_cb_##_opcode(uint8_t opcode) \
    {                                           \
        return set_u3_memhl(opcode, _bit);      \
    }                                           \
    register_opcode_cb_table(_opcode);

declare_set_u3_memhl(0xc6, 0);
declare_set_u3_memhl(0xce, 1);
declare_set_u3_memhl(0xd6, 2);
declare_set_u3_memhl(0xde, 3);
declare_set_u3_memhl(0xe6, 4);
declare_set_u3_memhl(0xee, 5);
declare_set_u3_memhl(0xf6, 6);
declare_set_u3_memhl(0xfe, 7);

/**
 * SWAP r8
 * cycles: 2
 * bytes: 2(0xcb included)
 */
static uint8_t swap_r8(uint8_t opcode, uint8_t *rd)
{
    uint8_t high = (*rd) & 0xf0;
    *rd <<= 4;
    *rd |= (high >> 4);

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(c_flag) = 0;
    reg_value(z_flag) = (*rd == 0);

    return cycles_cb_table[opcode];
}

#define declare_swap_r8(_opcode, _rd)           \
    uint8_t opcode_cb_##_opcode(uint8_t opcode) \
    {                                           \
        return swap_r8(opcode, reg(_rd));       \
    }                                           \
    register_opcode_cb_table(_opcode);

declare_swap_r8(0x30, b);
declare_swap_r8(0x31, c);
declare_swap_r8(0x32, d);
declare_swap_r8(0x33, e);
declare_swap_r8(0x34, h);
declare_swap_r8(0x35, l);
declare_swap_r8(0x37, a);

/**
 * SWAP [hl]
 * cycles: 4
 * bytes: 2(0xcb included)
 */
uint8_t opcode_cb_0x36(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));

    uint8_t high = value & 0xf0;
    value <<= 4;
    value |= (high >> 4);

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(c_flag) = 0;
    reg_value(z_flag) = (value == 0);

    bus_write(reg_value(hl), value);
    return cycles_cb_table[opcode];
}
register_opcode_cb_table(0x36);

/*Bit shift operations*/

/**
 * RL r8
 * cycles: 2
 * bytes: 2(0xcb included)
 */
static uint8_t rl_r8(uint8_t opcode, uint8_t *rd)
{
    uint8_t bit7 = ((*rd) & 0x80) >> 7;
    *rd <<= 1;
    *rd |= reg_value(c_flag);
    reg_value(c_flag) = bit7;

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (*rd == 0);

    return cycles_cb_table[opcode];
}

#define declare_rl_r8(_opcode, _rd)             \
    uint8_t opcode_cb_##_opcode(uint8_t opcode) \
    {                                           \
        return rl_r8(opcode, reg(_rd));         \
    }                                           \
    register_opcode_cb_table(_opcode);

declare_rl_r8(0x10, b);
declare_rl_r8(0x11, c);
declare_rl_r8(0x12, d);
declare_rl_r8(0x13, e);
declare_rl_r8(0x14, h);
declare_rl_r8(0x15, l);
declare_rl_r8(0x17, a);

/**
 * RL [hl]
 * cycles: 4
 * bytes: 2(0xcb included)
 */
uint8_t opcode_cb_0x16(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    uint8_t bit7 = (value & 0x80) >> 7;
    value <<= 1;
    value |= reg_value(c_flag);
    reg_value(c_flag) = bit7;
    bus_write(reg_value(hl), value);

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (value == 0);
    return cycles_cb_table[opcode];
}
register_opcode_cb_table(0x16);

/**
 * RLC r8
 * cycles: 2
 * bytes: 2(0xcb included)
 */
static uint8_t rlc_r8(uint8_t opcode, uint8_t *rd)
{
    uint8_t bit7 = ((*rd) & 0x80) >> 7;
    *rd <<= 1;
    *rd |= bit7;
    reg_value(c_flag) = bit7;

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (*rd == 0);
    return cycles_cb_table[opcode];
}
#define declare_rlc_r8(_opcode, _rd)            \
    uint8_t opcode_cb_##_opcode(uint8_t opcode) \
    {                                           \
        return rlc_r8(opcode, reg(_rd));        \
    }                                           \
    register_opcode_cb_table(_opcode);

declare_rlc_r8(0x00, b);
declare_rlc_r8(0x01, c);
declare_rlc_r8(0x02, d);
declare_rlc_r8(0x03, e);
declare_rlc_r8(0x04, h);
declare_rlc_r8(0x05, l);
declare_rlc_r8(0x07, a);

/**
 * RLC [hl]
 * cycles: 4
 * bytes: 2(0xcb included)
 */
uint8_t opcode_cb_0x06(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    uint8_t bit7 = (value & 0x80) >> 7;
    value <<= 1;
    value |= bit7;
    reg_value(c_flag) = bit7;
    bus_write(reg_value(hl), value);

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (value == 0);

    return cycles_cb_table[opcode];
}
register_opcode_cb_table(0x06);

/**
 * RLCA
 * cycles: 1
 * bytes: 1
 */
uint8_t opcode_0x07(uint8_t opcode)
{
    uint8_t bit7 = (reg_value(a) & 0x80) >> 7;
    reg_value(a) <<= 1;
    reg_value(a) |= bit7;
    reg_value(c_flag) = bit7;

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = 0;

    return cycles_table[opcode];
}
register_opcode_table(0x07);

/**
 * RLA
 * cycles: 1
 * bytes: 1
 */
uint8_t opcode_0x17(uint8_t opcode)
{
    uint8_t bit7 = (reg_value(a) & 0x80) >> 7;
    reg_value(a) <<= 1;
    reg_value(a) |= reg_value(c_flag);
    reg_value(c_flag) = bit7;

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = 0;

    return cycles_table[opcode];
}
register_opcode_table(0x17);

/**
 * RR r8
 * cycles: 2
 * bytes: 2(0xcb included)
 */
static uint8_t rr_r8(uint8_t opcode, uint8_t *rd)
{
    uint8_t bit0 = ((*rd) & 0x01);
    *rd >>= 1;
    *rd |= (reg_value(c_flag) << 7);
    reg_value(c_flag) = bit0;

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (*rd == 0);

    return cycles_cb_table[opcode];
}

#define declare_rr_r8(_opcode, _rd)             \
    uint8_t opcode_cb_##_opcode(uint8_t opcode) \
    {                                           \
        return rr_r8(opcode, reg(_rd));         \
    }                                           \
    register_opcode_cb_table(_opcode);

declare_rr_r8(0x18, b);
declare_rr_r8(0x19, c);
declare_rr_r8(0x1a, d);
declare_rr_r8(0x1b, e);
declare_rr_r8(0x1c, h);
declare_rr_r8(0x1d, l);
declare_rr_r8(0x1f, a);

/**
 * RR [hl]
 * cycles: 4
 * bytes: 2(0xcb included)
 */
uint8_t opcode_cb_0x1e(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    uint8_t bit0 = (value & 0x01);
    value >>= 1;
    value |= (reg_value(c_flag) << 7);
    reg_value(c_flag) = bit0;
    bus_write(reg_value(hl), value);

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (value == 0);

    return cycles_cb_table[opcode];
}
register_opcode_cb_table(0x1e);

/**
 * RRC r8
 * cycles: 2
 * bytes: 2(0xcb included)
 */
static uint8_t rrc_r8(uint8_t opcode, uint8_t *rd)
{
    uint8_t bit0 = ((*rd) & 0x01);
    *rd >>= 1;
    *rd |= (bit0 << 7);
    reg_value(c_flag) = bit0;

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (*rd == 0);

    return cycles_cb_table[opcode];
}
#define declare_rrc_r8(_opcode, _rd)            \
    uint8_t opcode_cb_##_opcode(uint8_t opcode) \
    {                                           \
        return rrc_r8(opcode, reg(_rd));        \
    }                                           \
    register_opcode_cb_table(_opcode);

declare_rrc_r8(0x08, b);
declare_rrc_r8(0x09, c);
declare_rrc_r8(0x0a, d);
declare_rrc_r8(0x0b, e);
declare_rrc_r8(0x0c, h);
declare_rrc_r8(0x0d, l);
declare_rrc_r8(0x0f, a);

/**
 * RRC [hl]
 * cycles: 4
 * bytes: 2(0xcb included)
 */
uint8_t opcode_cb_0x0e(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    uint8_t bit0 = (value & 0x01);
    value >>= 1;
    value |= (bit0 << 7);
    reg_value(c_flag) = bit0;
    bus_write(reg_value(hl), value);

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (value == 0);

    return cycles_cb_table[opcode];
}
register_opcode_cb_table(0x0e);

/**
 * RRCA
 * cycles: 1
 * bytes: 1
 */
uint8_t opcode_0x0f(uint8_t opcode)
{
    uint8_t bit0 = (reg_value(a) & 0x01);
    reg_value(a) >>= 1;
    reg_value(a) |= (bit0 << 7);
    reg_value(c_flag) = bit0;

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = 0;

    return cycles_table[opcode];
}
register_opcode_table(0x0f);

/**
 * RRA
 * cycles: 1
 * bytes: 1
 */
uint8_t opcode_0x1f(uint8_t opcode)
{
    uint8_t bit0 = (reg_value(a) & 0x01);
    reg_value(a) >>= 1;
    reg_value(a) |= (reg_value(c_flag) << 7);
    reg_value(c_flag) = bit0;

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = 0;

    return cycles_table[opcode];
}
register_opcode_table(0x1f);

/**
 * SLA r8
 * cycles: 2
 * bytes: 2(0xcb included)
 */
static uint8_t sla_r8(uint8_t opcode, uint8_t *rd)
{
    uint8_t bit7 = ((*rd) & 0x80) >> 7;
    *rd <<= 1;
    *rd &= 0xfe;
    reg_value(c_flag) = bit7;

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (*rd == 0);

    return cycles_cb_table[opcode];
}

#define declare_sla_r8(_opcode, _rd)            \
    uint8_t opcode_cb_##_opcode(uint8_t opcode) \
    {                                           \
        return sla_r8(opcode, reg(_rd));        \
    }                                           \
    register_opcode_cb_table(_opcode);

declare_sla_r8(0x20, b);
declare_sla_r8(0x21, c);
declare_sla_r8(0x22, d);
declare_sla_r8(0x23, e);
declare_sla_r8(0x24, h);
declare_sla_r8(0x25, l);
declare_sla_r8(0x27, a);

/**
 * SLA [hl]
 * cycles: 4
 * bytes: 2(0xcb included)
 */
uint8_t opcode_cb_0x26(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    uint8_t bit7 = (value & 0x80) >> 7;
    value <<= 1;
    value &= 0xfe;
    reg_value(c_flag) = bit7;
    bus_write(reg_value(hl), value);

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (value == 0);

    return cycles_cb_table[opcode];
}
register_opcode_cb_table(0x26);

/**
 * SRA r8
 * cycless: 2
 * bytes: 2(0xcb included)
 */
static uint8_t sra_r8(uint8_t opcode, uint8_t *rd)
{
    uint8_t bit0 = ((*rd) & 0x01);
    uint8_t bit7 = ((*rd) & 0x80) >> 7;

    *rd >>= 1;
    if (bit7)
        *rd |= 0x80;
    else
        *rd &= 0x7f;

    reg_value(c_flag) = bit0;
    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (*rd == 0);

    return cycles_cb_table[opcode];
}

#define declare_sra_r8(_opcode, _rd)            \
    uint8_t opcode_cb_##_opcode(uint8_t opcode) \
    {                                           \
        return sra_r8(opcode, reg(_rd));        \
    }                                           \
    register_opcode_cb_table(_opcode);

declare_sra_r8(0x28, b);
declare_sra_r8(0x29, c);
declare_sra_r8(0x2a, d);
declare_sra_r8(0x2b, e);
declare_sra_r8(0x2c, h);
declare_sra_r8(0x2d, l);
declare_sra_r8(0x2f, a);

/**
 * SRA [hl]
 * cycles: 4
 * bytes: 2(0xcb included)
 */
uint8_t opcode_cb_0x2e(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    uint8_t bit0 = (value & 0x01);
    uint8_t bit7 = (value & 0x80) >> 7;

    value >>= 1;
    if (bit7)
        value |= 0x80;
    else
        value &= 0x7f;

    reg_value(c_flag) = bit0;
    bus_write(reg_value(hl), value);

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (value);

    return cycles_cb_table[opcode];
}
register_opcode_cb_table(0x2e);

/**
 * SRL r8
 * cycles: 2
 * bytes: 2(0xcb included)
 */
static uint8_t srl_r8(uint8_t opcode, uint8_t *rd)
{
    uint8_t bit0 = ((*rd) & 0x01);
    *rd >>= 1;
    *rd &= 0x7f;
    reg_value(c_flag) = bit0;

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (*rd == 0);

    return cycles_cb_table[opcode];
}

#define declare_srl_r8(_opcode, _rd)            \
    uint8_t opcode_cb_##_opcode(uint8_t opcode) \
    {                                           \
        return srl_r8(opcode, reg(_rd));        \
    }                                           \
    register_opcode_cb_table(_opcode);

declare_srl_r8(0x38, b);
declare_srl_r8(0x39, c);
declare_srl_r8(0x3a, d);
declare_srl_r8(0x3b, e);
declare_srl_r8(0x3c, h);
declare_srl_r8(0x3d, l);
declare_srl_r8(0x3f, a);

/**
 * SRL [hl]
 * cycles: 4
 * bytes: 2(0xcb included)
 */
uint8_t opcode_cb_0x3e(uint8_t opcode)
{
    uint8_t value = bus_read(reg_value(hl));
    uint8_t bit0 = (value & 0x01);
    value >>= 1;
    value &= 0x7f;
    reg_value(c_flag) = bit0;
    bus_write(reg_value(hl), value);

    reg_value(n_flag) = 0;
    reg_value(h_flag) = 0;
    reg_value(z_flag) = (value == 0);

    return cycles_cb_table[opcode];
}
register_opcode_cb_table(0x3e);
