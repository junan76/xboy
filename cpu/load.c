#include <xboy.h>
#include "cpu-internal.h"

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
    }

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
 */
#define LD_R8_N8(_opcode, _rd)               \
    void opcode_##_opcode(uint8_t opcode)    \
    {                                        \
        (void)opcode;                        \
        uint8_t *__rd = reg(_rd);            \
        uint8_t __value = read_byte_by_pc(); \
        *__rd = __value;                     \
    }

LD_R8_N8(0x06, b)
LD_R8_N8(0x0e, c)
LD_R8_N8(0x16, d)
LD_R8_N8(0x1e, e)
LD_R8_N8(0x26, h)
LD_R8_N8(0x2e, l)
LD_R8_N8(0x3e, a)

void load_init()
{
}