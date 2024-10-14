#include <xboy.h>
#include "cpu-internal.h"

#define __register_opcode_table(_opcode)                                   \
    __attribute__((constructor)) static void opcode_##_opcode##_init(void) \
    {                                                                      \
        opcode_table[_opcode] = opcode_##_opcode;                          \
    }

/**
 * ld r8, r8
 */
#define LD_R8_R8(_opcode, _rd, _rs)       \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        (void)opcode;                     \
        uint8_t *__rd = reg(_rd);         \
        uint8_t *__rs = reg(_rs);         \
        *__rd = *__rs;                    \
    }                                     \
    __register_opcode_table(_opcode)

/*ld b, r8*/
LD_R8_R8(0x40, b, b)
LD_R8_R8(0x41, b, c)
LD_R8_R8(0x42, b, d)
LD_R8_R8(0x43, b, e)
LD_R8_R8(0x44, b, h)
LD_R8_R8(0x45, b, l)
LD_R8_R8(0x47, b, a)

/*ld c, r8*/
LD_R8_R8(0x48, c, b)
LD_R8_R8(0x49, c, c)
LD_R8_R8(0x4a, c, d)
LD_R8_R8(0x4b, c, e)
LD_R8_R8(0x4c, c, h)
LD_R8_R8(0x4d, c, l)
LD_R8_R8(0x4f, c, a)

/*ld d, r8*/
LD_R8_R8(0x50, d, b)
LD_R8_R8(0x51, d, c)
LD_R8_R8(0x52, d, d)
LD_R8_R8(0x53, d, e)
LD_R8_R8(0x54, d, h)
LD_R8_R8(0x55, d, l)
LD_R8_R8(0x57, d, a)

/*ld e, r8*/
LD_R8_R8(0x58, e, b)
LD_R8_R8(0x59, e, c)
LD_R8_R8(0x5a, e, d)
LD_R8_R8(0x5b, e, e)
LD_R8_R8(0x5c, e, h)
LD_R8_R8(0x5d, e, l)
LD_R8_R8(0x5f, e, a)

/*ld h, r8*/
LD_R8_R8(0x60, h, b)
LD_R8_R8(0x61, h, c)
LD_R8_R8(0x62, h, d)
LD_R8_R8(0x63, h, e)
LD_R8_R8(0x64, h, h)
LD_R8_R8(0x65, h, l)
LD_R8_R8(0x67, h, a)

/*ld l, r8*/
LD_R8_R8(0x68, l, b)
LD_R8_R8(0x69, l, c)
LD_R8_R8(0x6a, l, d)
LD_R8_R8(0x6b, l, e)
LD_R8_R8(0x6c, l, h)
LD_R8_R8(0x6d, l, l)
LD_R8_R8(0x6f, l, a)

/*ld a, r8*/
LD_R8_R8(0x78, a, b)
LD_R8_R8(0x79, a, c)
LD_R8_R8(0x7a, a, d)
LD_R8_R8(0x7b, a, e)
LD_R8_R8(0x7c, a, h)
LD_R8_R8(0x7d, a, l)
LD_R8_R8(0x7f, a, a)

/**
 * ld r8, n8
 * cycles: 2
 * bytes: 2
 */
#define LD_R8_N8(_opcode, _rd)               \
    void opcode_##_opcode(uint8_t opcode)    \
    {                                        \
        (void)opcode;                        \
        uint8_t *__rd = reg(_rd);            \
        uint8_t __value = read_byte_by_pc(); \
        *__rd = __value;                     \
    }                                        \
    __register_opcode_table(_opcode)

LD_R8_N8(0x06, b)
LD_R8_N8(0x0e, c)
LD_R8_N8(0x16, d)
LD_R8_N8(0x1e, e)
LD_R8_N8(0x26, h)
LD_R8_N8(0x2e, l)
LD_R8_N8(0x3e, a)

/**
 * ld r16, n16
 * cycles: 3
 * bytes: 3
 */
#define LD_R16_N16(_opcode, _rd)              \
    void opcode_##_opcode(uint8_t opcode)     \
    {                                         \
        uint16_t __value = read_word_by_pc(); \
        uint16_t *__rd = reg(_rd);            \
        *__rd = __value;                      \
    }                                         \
    __register_opcode_table(_opcode)

LD_R16_N16(0x01, bc)
LD_R16_N16(0x11, de)
LD_R16_N16(0x21, hl)

/**
 * ld [hl], r8
 * cycles: 2
 * bytes: 1
 */
#define LD_MEMHL_R8(_opcode, _rs)         \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        uint8_t __value = reg_value(_rs); \
        uint16_t __addr = reg_value(hl);  \
        bus_write(__addr, __value);       \
    }                                     \
    __register_opcode_table(_opcode)

LD_MEMHL_R8(0x70, b)
LD_MEMHL_R8(0x71, c)
LD_MEMHL_R8(0x72, d)
LD_MEMHL_R8(0x73, e)
LD_MEMHL_R8(0x74, h)
LD_MEMHL_R8(0x75, l)
LD_MEMHL_R8(0x77, a)

/**
 * ld [hl], n8
 * cycles: 3
 * bytes: 2
 */
#define LD_MEMHL_N8(_opcode)                 \
    void opcode_##_opcode(uint8_t opcode)    \
    {                                        \
        uint8_t __value = read_byte_by_pc(); \
        uint16_t __addr = reg_value(hl);     \
        bus_write(__addr, __value);          \
    }                                        \
    __register_opcode_table(_opcode)

LD_MEMHL_N8(0x36)

/**
 * ld r8, [hl]
 */
#define LD_R8_MEMHL(_opcode, _rd)           \
    void opcode_##_opcode(uint8_t opcode)   \
    {                                       \
        uint16_t __addr = reg_value(hl);    \
        uint8_t __value = bus_read(__addr); \
        uint8_t *__rd = reg(_rd);           \
        *__rd = __value;                    \
    }                                       \
    __register_opcode_table(_opcode)

LD_R8_MEMHL(0x46, b)
LD_R8_MEMHL(0x4e, c)
LD_R8_MEMHL(0x56, d)
LD_R8_MEMHL(0x5e, e)
LD_R8_MEMHL(0x66, h)
LD_R8_MEMHL(0x6e, l)
LD_R8_MEMHL(0x7e, a)

/**
 * ld [r16], a
 * cycles: 2
 * bytes: 1
 */
#define LD_MEMR16_A(_opcode, _memr16)         \
    void opcode_##_opcode(uint8_t opcode)     \
    {                                         \
        uint8_t __value = reg_value(a);       \
        uint16_t __addr = reg_value(_memr16); \
        bus_write(__addr, __value);           \
    }                                         \
    __register_opcode_table(_opcode)

LD_MEMR16_A(0x02, bc)
LD_MEMR16_A(0x12, de)

/**
 * ld [n16], a
 * cycles: 4
 * bytes: 3
 */
#define LD_MEMN16_A(_opcode)                 \
    void opcode_##_opcode(uint8_t opcode)    \
    {                                        \
        uint8_t __value = reg_value(a);      \
        uint16_t __addr = read_word_by_pc(); \
        bus_write(__addr, __value);          \
    }                                        \
    __register_opcode_table(_opcode);

LD_MEMN16_A(0xea)

/**
 * ldh [n16], a
 * cycles: 3
 * bytes: 2
 */
#define LDH_MEMN16_A(_opcode)                         \
    void opcode_##_opcode(uint8_t opcode)             \
    {                                                 \
        uint8_t __value = reg_value(a);               \
        uint16_t __addr = 0xFF00 + read_byte_by_pc(); \
        bus_write(__addr, __value);                   \
    }                                                 \
    __register_opcode_table(_opcode)

LDH_MEMN16_A(0xe0)

/**
 * ldh [c], a
 * cycles: 2
 * bytes: 1
 */
#define LDH_MEMC_A(_opcode)                      \
    void opcode_##_opcode(uint8_t opcode)        \
    {                                            \
        uint8_t __value = reg_value(a);          \
        uint16_t __addr = 0xFF00 + reg_value(c); \
        bus_write(__addr, __value);              \
    }                                            \
    __register_opcode_table(_opcode)

LDH_MEMC_A(0xe2)

/**
 * ld a, [r16]
 * cycles: 2
 * bytes: 1
 */
#define LD_A_MEMR16(_opcode, _rs)           \
    void opcode_##_opcode(uint8_t opcode)   \
    {                                       \
        uint8_t *__rd = reg(a);             \
        uint16_t __addr = reg_value(_rs);   \
        uint8_t __value = bus_read(__addr); \
        *__rd = __value;                    \
    }                                       \
    __register_opcode_table(_opcode)

LD_A_MEMR16(0x0a, bc)
LD_A_MEMR16(0x1a, de)

/**
 * ld a, [n16]
 * cycles: 4
 * bytes: 3
 */
#define LD_A_MEMN16(_opcode)                 \
    void opcode_##_opcode(uint8_t opcode)    \
    {                                        \
        uint16_t __addr = read_word_by_pc(); \
        uint8_t __value = bus_read(__addr);  \
        uint8_t *__rd = reg(a);              \
        *__rd = __value;                     \
    }                                        \
    __register_opcode_table(_opcode)

LD_A_MEMN16(0xfa)

/**
 * ldh a, [n16]
 * cycles: 3
 * bytes: 2
 */
#define LDH_A_MEMN16(_opcode)                         \
    void opcode_##_opcode(uint8_t opcode)             \
    {                                                 \
        uint16_t __addr = 0xFF00 + read_byte_by_pc(); \
        uint8_t __value = bus_read(__addr);           \
        uint8_t *__rd = reg(a);                       \
        *__rd = __value;                              \
    }                                                 \
    __register_opcode_table(_opcode)

LDH_A_MEMN16(0xf0)

/**
 * ldh a, [c]
 * cycles: 2
 * bytes: 1
 */
#define LDH_A_MEMC(_opcode)                      \
    void opcode_##_opcode(uint8_t opcode)        \
    {                                            \
        uint16_t __addr = 0xFF00 + reg_value(c); \
        uint8_t *__rd = reg(a);                  \
        *__rd = bus_read(__addr);                \
    }                                            \
    __register_opcode_table(_opcode)

LDH_A_MEMC(0xf2)

/**
 * ld [hl+], a
 * cycles: 2
 * bytes: 1
 */
#define LD_MEMHLI_A(_opcode)              \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        uint8_t __value = reg_value(a);   \
        uint16_t *__rd = reg(hl);         \
        bus_write(*__rd, __value);        \
        *__rd += 1;                       \
    }                                     \
    __register_opcode_table(_opcode)

LD_MEMHLI_A(0x22)

/**
 * ld, [hl-], a
 * cycles: 2
 * bytes: 1
 */
#define LD_MEMHLD_A(_opcode)              \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        uint8_t __value = reg_value(a);   \
        uint16_t *__rd = reg(hl);         \
        bus_write(*__rd, __value);        \
        *__rd -= 1;                       \
    }                                     \
    __register_opcode_table(_opcode)

LD_MEMHLD_A(0x32)

/**
 * ld a, [hl-]
 * cycles: 2
 * bytes: 1
 */
#define LD_A_MEMHLD(_opcode)              \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        uint16_t *__rs = reg(hl);         \
        uint8_t *__rd = reg(a);           \
        *__rd = bus_read(*__rs);          \
        *__rs -= 1;                       \
    }                                     \
    __register_opcode_table(_opcode)

LD_A_MEMHLD(0x3a)

/**
 * ld a, [hl+]
 * cycles: 2
 * bytes: 1
 */
#define LD_A_MEMHLI(_opcode)              \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        uint16_t *__rs = reg(hl);         \
        uint8_t *__rd = reg(a);           \
        *__rd = bus_read(*__rs);          \
        *__rs += 1;                       \
    }                                     \
    __register_opcode_table(_opcode)

LD_A_MEMHLI(0x2a)

/**
 * ld sp, n16
 * cycles: 3
 * bytes: 3
 */
#define LD_SP_N16(_opcode)                    \
    void opcode_##_opcode(uint8_t opcode)     \
    {                                         \
        uint16_t __value = read_word_by_pc(); \
        reg_value(sp) = __value;              \
    }                                         \
    __register_opcode_table(_opcode)

LD_SP_N16(0x31)

/**
 * ld [n16], sp
 * cycles: 5
 * bytes: 3
 */
#define LD_MEMN16_SP(_opcode)                         \
    void opcode_##_opcode(uint8_t opcode)             \
    {                                                 \
        uint16_t __addr = read_word_by_pc();          \
        uint16_t __value = reg_value(sp);             \
        bus_write(__addr, __value & 0xff);            \
        bus_write(__addr + 1, (__value >> 8) & 0xff); \
    }                                                 \
    __register_opcode_table(_opcode)

LD_MEMN16_SP(0x08)

/**
 * ld hl, sp+e8
 * cycles: 3
 * bytes: 2
 * TODO: handle carry and half_carry flag
 */
#define LD_HL_SPE8(_opcode)               \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        int8_t __e8 = read_byte_by_pc();  \
        uint16_t *__rd = reg(hl);         \
        uint16_t __value = 0;             \
        *__rd = __value;                  \
    }                                     \
    __register_opcode_table(_opcode)

LD_HL_SPE8(0xf8)

/**
 * ld sp, hl
 * cycles: 2
 * bytes: 1
 */
#define LD_SP_HL(_opcode)                 \
    void opcode_##_opcode(uint8_t opcode) \
    {                                     \
        reg_value(sp) = reg_value(hl);    \
    }                                     \
    __register_opcode_table(_opcode)

LD_SP_HL(0xf9)