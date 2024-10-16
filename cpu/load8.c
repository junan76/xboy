#include <xboy.h>
#include "cpu-internal.h"

/**
 * LD r8, r8
 * cycles: 1
 * bytes: 1
 */
static void ld_r8_r8(uint8_t opcode, uint8_t *rd, uint8_t *rs)
{
    *rd = *rs;
}

#define declare_ld_r8r8(_opcode, _rd, _rs)    \
    void opcode_##_opcode(uint8_t opcode)     \
    {                                         \
        ld_r8_r8(opcode, reg(_rd), reg(_rs)); \
    }                                         \
    register_opcode_table(_opcode)

declare_ld_r8r8(0x40, b, b);
declare_ld_r8r8(0x41, b, c);
declare_ld_r8r8(0x42, b, d);
declare_ld_r8r8(0x43, b, e);
declare_ld_r8r8(0x44, b, h);
declare_ld_r8r8(0x45, b, l);
declare_ld_r8r8(0x47, b, a);

declare_ld_r8r8(0x48, c, b);
declare_ld_r8r8(0x49, c, c);
declare_ld_r8r8(0x4a, c, d);
declare_ld_r8r8(0x4b, c, e);
declare_ld_r8r8(0x4c, c, h);
declare_ld_r8r8(0x4d, c, l);
declare_ld_r8r8(0x4f, c, a);

declare_ld_r8r8(0x50, d, b);
declare_ld_r8r8(0x51, d, c);
declare_ld_r8r8(0x52, d, d);
declare_ld_r8r8(0x53, d, e);
declare_ld_r8r8(0x54, d, h);
declare_ld_r8r8(0x55, d, l);
declare_ld_r8r8(0x57, d, a);

declare_ld_r8r8(0x58, e, b);
declare_ld_r8r8(0x59, e, c);
declare_ld_r8r8(0x5a, e, d);
declare_ld_r8r8(0x5b, e, e);
declare_ld_r8r8(0x5c, e, h);
declare_ld_r8r8(0x5d, e, l);
declare_ld_r8r8(0x5f, e, a);

declare_ld_r8r8(0x60, h, b);
declare_ld_r8r8(0x61, h, c);
declare_ld_r8r8(0x62, h, d);
declare_ld_r8r8(0x63, h, e);
declare_ld_r8r8(0x64, h, h);
declare_ld_r8r8(0x65, h, l);
declare_ld_r8r8(0x67, h, a);

declare_ld_r8r8(0x68, l, b);
declare_ld_r8r8(0x69, l, c);
declare_ld_r8r8(0x6a, l, d);
declare_ld_r8r8(0x6b, l, e);
declare_ld_r8r8(0x6c, l, h);
declare_ld_r8r8(0x6d, l, l);
declare_ld_r8r8(0x6f, l, a);

declare_ld_r8r8(0x78, a, b);
declare_ld_r8r8(0x79, a, c);
declare_ld_r8r8(0x7a, a, d);
declare_ld_r8r8(0x7b, a, e);
declare_ld_r8r8(0x7c, a, h);
declare_ld_r8r8(0x7d, a, l);
declare_ld_r8r8(0x7f, a, a);

/**
 * LD [hl], r8
 * cycles: 2
 * bytes: 1
 */

static void ld_memhl_r8(uint8_t opcode, uint8_t *rs)
{
    uint16_t addr = reg_value(hl);
    bus_write(addr, *rs);
}

#define declare_ld_memhl_r8(_opcode, _rs) \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        ld_memhl_r8(opcode, reg(_rs));    \
    }                                     \
    register_opcode_table(_opcode)

declare_ld_memhl_r8(0x70, b);
declare_ld_memhl_r8(0x71, c);
declare_ld_memhl_r8(0x72, d);
declare_ld_memhl_r8(0x73, e);
declare_ld_memhl_r8(0x74, h);
declare_ld_memhl_r8(0x75, l);
declare_ld_memhl_r8(0x77, a);

/**
 * LD r8, [hl]
 * cycles: 2
 * bytes: 1
 */
static void ld_r8_memhl(uint8_t opcode, uint8_t *rd)
{
    *rd = bus_read(reg_value(hl));
}
#define declare_ld_r8_memhl(_opcode, _rd) \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        ld_r8_memhl(opcode, reg(_rd));    \
    }                                     \
    register_opcode_table(_opcode)

declare_ld_r8_memhl(0x46, b);
declare_ld_r8_memhl(0x4e, c);
declare_ld_r8_memhl(0x56, d);
declare_ld_r8_memhl(0x5e, e);
declare_ld_r8_memhl(0x66, h);
declare_ld_r8_memhl(0x6e, l);
declare_ld_r8_memhl(0x7e, a);

/**
 * LD r8, n8
 * cycles: 2
 * bytes: 2
 */
static void ld_r8n8(uint8_t opcode, uint8_t *rd)
{
    uint8_t value = read_byte_by_pc();
    *rd = value;
}

#define declare_ld_r8n8(_opcode, _rd)     \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        ld_r8n8(opcode, reg(_rd));        \
    }                                     \
    register_opcode_table(_opcode)

declare_ld_r8n8(0x06, b);
declare_ld_r8n8(0x0e, c);
declare_ld_r8n8(0x16, d);
declare_ld_r8n8(0x1e, e);
declare_ld_r8n8(0x26, h);
declare_ld_r8n8(0x2e, l);
declare_ld_r8n8(0x3e, a);

/**
 * LD [hl], n8
 * cycles: 3
 * bytes: 2
 */

static void ld_memhl_n8(uint8_t opcode)
{
    uint8_t value = read_byte_by_pc();
    uint16_t addr = reg_value(hl);
    bus_write(addr, value);
}

void opcode_0x36(uint8_t opcode)
{
    ld_memhl_n8(opcode);
}
register_opcode_table(0x36);

/**
 * LD [r16], a
 * cycles: 2
 * bytes: 1
 */
static void ld_memr16_a(uint8_t opcode, uint16_t addr)
{
    bus_write(addr, reg_value(a));
}

#define declare_ld_memr16_a(_opcode, _rd)    \
    void opcode_##_opcode(uint8_t opcode)    \
    {                                        \
        ld_memr16_a(opcode, reg_value(_rd)); \
    }                                        \
    register_opcode_table(_opcode)

declare_ld_memr16_a(0x02, bc);
declare_ld_memr16_a(0x12, de);

/**
 * LD a, [r16]
 * cycles: 2
 * bytes: 1
 */
static void ld_a_memr16(uint8_t opcode, uint16_t addr)
{
    reg_value(a) = bus_read(addr);
}

#define declare_ld_a_memr16(_opcode, _rs)    \
    void opcode_##_opcode(uint8_t opcode)    \
    {                                        \
        ld_a_memr16(opcode, reg_value(_rs)); \
    }                                        \
    register_opcode_table(_opcode)

declare_ld_a_memr16(0x0a, bc);
declare_ld_a_memr16(0x1a, de);

/**
 * LD [hl+], a
 * cycles: 2
 * bytes: 1
 */
static void ldi_memhl_a(uint8_t opcode)
{
    bus_write(reg_value(hl), reg_value(a));
    reg_value(hl) += 1;
}

void opcode_0x22(uint8_t opcode)
{
    ldi_memhl_a(opcode);
}
register_opcode_table(0x22);

/**
 * LD, [hl-], a
 * cycles: 2
 * bytes: 1
 */
static void ldd_memhl_a(uint8_t opcode)
{
    bus_write(reg_value(hl), reg_value(a));
    reg_value(hl) -= 1;
}

void opcode_0x32(uint8_t opcode)
{
    ldd_memhl_a(opcode);
}
register_opcode_table(0x32);

/**
 * LD a, [hl+]
 * cycles: 2
 * bytes: 1
 */
static void ldi_a_memhl(uint8_t opcode)
{
    reg_value(a) = bus_read(reg_value(hl));
    reg_value(hl) += 1;
}

void opcode_0x2a(uint8_t opcode)
{
    ldi_a_memhl(opcode);
}
register_opcode_table(0x2a);

/**
 * LD a, [hl-]
 * cycles: 2
 * bytes: 1
 */
static void ldd_a_memhl(uint8_t opcode)
{
    reg_value(a) = bus_read(reg_value(hl));
    reg_value(hl) -= 1;
}

void opcode_0x3a(uint8_t opcode)
{
    ldd_a_memhl(opcode);
}
register_opcode_table(0x3a);

/**
 * LDH [a8], a
 * cycles: 3
 * bytes: 2
 */
static void ldh_mema8_a(uint8_t opcode)
{
    uint16_t addr = 0xff00 + read_byte_by_pc();
    bus_write(addr, reg_value(a));
}

void opcode_0xe0(uint8_t opcode)
{
    ldh_mema8_a(opcode);
}
register_opcode_table(0xe0);

/**
 * LDH a, [a8]
 * cycles: 3
 * bytes: 2
 */
static void ldh_a_mema8(uint8_t opcode)
{
    uint8_t offset = read_byte_by_pc();
    reg_value(a) = bus_read(0xff00 + offset);
}

void opcode_0xf0(uint8_t opcode)
{
    ldh_a_mema8(opcode);
}
register_opcode_table(0xf0);

/**
 * LDH [c], a
 * cycles: 2
 * bytes: 1
 */
static void ldh_memc_a(uint8_t opcode)
{
    uint16_t addr = 0xff00 + reg_value(c);
    bus_write(addr, reg_value(a));
}

void opcode_0xe2(uint8_t opcode)
{
    ldh_memc_a(opcode);
}
register_opcode_table(0xe2);

/**
 * LDH a, [c]
 * cycles: 2
 * bytes: 1
 */
static void ldh_a_memc(uint8_t opcode)
{
    uint16_t addr = 0xff00 + reg_value(c);
    reg_value(a) = bus_read(addr);
}

void opcode_0xf2(uint8_t opcode)
{
    ldh_a_memc(opcode);
}
register_opcode_table(0xf2);

/**
 * LD [a16], a
 * cycles: 4
 * bytes: 3
 */
static void ld_mema16_a(uint8_t opcode)
{
    uint16_t addr = read_word_by_pc();
    bus_write(addr, reg_value(a));
}

void opcode_0xea(uint8_t opcode)
{
    ld_mema16_a(opcode);
}
register_opcode_table(0xea);

/**
 * LD a, [n16]
 * cycles: 4
 * bytes: 3
 */
static void ld_a_a16mem(uint8_t opcode)
{
    uint16_t addr = read_word_by_pc();
    reg_value(a) = bus_read(addr);
}

void opcode_0xfa(uint8_t opcode)
{
    ld_a_a16mem(opcode);
}
register_opcode_table(0xfa);
