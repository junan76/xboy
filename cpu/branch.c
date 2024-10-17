#include <xboy.h>
#include "cpu-internal.h"

enum condition_code
{
    cc_Z,
    cc_NZ,
    cc_C,
    cc_NC,
};

enum rst_vec
{
    rst0 = 0x00,
    rst1 = 0x08,
    rst2 = 0x10,
    rst3 = 0x18,
    rst4 = 0x20,
    rst5 = 0x28,
    rst6 = 0x30,
    rst7 = 0x38,
};

/**
 * Stack push/pop operations
 */
static void push_stack(uint8_t value)
{
    bus_write(--reg_value(sp), value);
}

static uint8_t pop_stack()
{
    return bus_read(reg_value(sp)++);
}

/**
 * JR e8
 * cycles: 3
 * bytes: 2
 */
uint8_t opcode_0x18(uint8_t opcode)
{
    int8_t offset = read_byte_by_pc();
    reg_value(pc) += offset;
    return cycles_table[opcode];
}
register_opcode_table(0x18);

/**
 * JR cc, e8
 * cycles: 3 taken / 2 untaken
 * bytes: 2
 */
static uint8_t jr_cc_e8(uint8_t opcode, enum condition_code cc)
{
    uint8_t taken = 0;
    int8_t offset = read_byte_by_pc();

    taken |= (cc == cc_Z && reg_value(z_flag) == 1);
    taken |= (cc == cc_NZ && reg_value(z_flag) == 0);
    taken |= (cc == cc_C && reg_value(c_flag) == 1);
    taken |= (cc == cc_NC && reg_value(c_flag) == 0);

    if (taken)
    {
        reg_value(pc) += offset;
        return cycles_table[opcode] + 1;
    }
    return cycles_table[opcode];
}

#define declare_jr_cc_e8(_opcode, _cc)       \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return jr_cc_e8(opcode, _cc);        \
    }                                        \
    register_opcode_table(_opcode);

declare_jr_cc_e8(0x20, cc_NZ);
declare_jr_cc_e8(0x28, cc_Z);
declare_jr_cc_e8(0x30, cc_NC);
declare_jr_cc_e8(0x38, cc_C);

/**
 * JP n16
 * cycles: 4
 * bytes: 3
 */
uint8_t opcode_0xc3(uint8_t opcode)
{
    reg_value(pc) = read_word_by_pc();
    return cycles_table[opcode];
}
register_opcode_table(0xc3);

/**
 * JP cc, n16
 * cycles: 4 taken / 3 untaken
 * bytes: 3
 */
static uint8_t jp_cc_n16(uint8_t opcode, enum condition_code cc)
{
    uint8_t taken = 0;
    uint16_t jpaddr = read_word_by_pc();

    taken |= (cc == cc_Z && reg_value(z_flag) == 1);
    taken |= (cc == cc_NZ && reg_value(z_flag) == 0);
    taken |= (cc == cc_C && reg_value(c_flag) == 1);
    taken |= (cc == cc_NC && reg_value(c_flag) == 0);

    if (taken)
    {
        reg_value(pc) = jpaddr;
        return cycles_table[opcode] + 1;
    }
    return cycles_table[opcode];
}

#define declare_jp_cc_n16(_opcode, _cc)      \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return jp_cc_n16(opcode, _cc);       \
    }                                        \
    register_opcode_table(_opcode);

declare_jp_cc_n16(0xc2, cc_NZ);
declare_jp_cc_n16(0xca, cc_Z);
declare_jp_cc_n16(0xd2, cc_NC);
declare_jp_cc_n16(0xda, cc_C);

/**
 * CALL n16
 * cycles: 6
 * bytes: 3
 */
uint8_t opcode_0xcd(uint8_t opcode)
{
    uint16_t call_addr = read_byte_by_pc();
    push_stack((reg_value(pc) >> 8) & 0xff);
    push_stack(reg_value(pc) & 0xff);
    reg_value(pc) = call_addr;
    return cycles_table[opcode];
}
register_opcode_table(0xcd);

/**
 * CALL cc, n16
 * cycles: 6 taken / 3 untaken
 * bytes: 3
 */
static uint8_t call_cc_n16(uint8_t opcode, enum condition_code cc)
{

    uint8_t taken = 0;
    uint16_t call_addr = read_word_by_pc();

    taken |= (cc == cc_Z && reg_value(z_flag) == 1);
    taken |= (cc == cc_NZ && reg_value(z_flag) == 0);
    taken |= (cc == cc_C && reg_value(c_flag) == 1);
    taken |= (cc == cc_NC && reg_value(c_flag) == 0);

    if (taken)
    {
        push_stack((reg_value(pc) >> 8) & 0xff);
        push_stack(reg_value(pc) & 0xff);
        reg_value(pc) = call_addr;
        return cycles_table[opcode] + 3;
    }
    return cycles_table[opcode];
}

#define declare_call_cc_n16(_opcode, _cc)    \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return call_cc_n16(opcode, _cc);     \
    }                                        \
    register_opcode_table(_opcode);

declare_call_cc_n16(0xc4, cc_NZ);
declare_call_cc_n16(0xcc, cc_Z);
declare_call_cc_n16(0xd4, cc_NC);
declare_call_cc_n16(0xdc, cc_C);

/**
 * RET
 * cycles: 4
 * bytes: 1
 */
uint8_t opcode_0xc9(uint8_t opcode)
{
    reg_value(pc) = pop_stack() | (pop_stack() << 8);
    return cycles_table[opcode];
}
register_opcode_table(0xc9);

/**
 * RETI
 * cycles: 4
 * bytes: 1
 */
uint8_t opcode_0xd9(uint8_t opcode)
{
    reg_value(pc) = pop_stack() | (pop_stack() << 8);
    cpu.interrupts.ime = 1;
    return cycles_table[opcode];
}
register_opcode_table(0xd9);

/**
 * RET cc
 * cycles: 5 taken / 2 untaken
 * bytes: 1
 */
static uint8_t ret_cc(uint8_t opcode, enum condition_code cc)
{
    uint8_t taken = 0;

    taken |= (cc == cc_Z && reg_value(z_flag) == 1);
    taken |= (cc == cc_NZ && reg_value(z_flag) == 0);
    taken |= (cc == cc_C && reg_value(c_flag) == 1);
    taken |= (cc == cc_NC && reg_value(c_flag) == 0);

    if (taken)
    {
        reg_value(pc) = pop_stack() | (pop_stack() << 8);
        return cycles_table[opcode] + 3;
    }
    return cycles_table[opcode];
}

#define declare_ret_cc(_opcode, _cc)         \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return ret_cc(opcode, _cc);          \
    }                                        \
    register_opcode_table(_opcode);

declare_ret_cc(0xc0, cc_NZ);
declare_ret_cc(0xc8, cc_Z);
declare_ret_cc(0xd0, cc_NC);
declare_ret_cc(0xd8, cc_C);

/**
 * RST vec
 * cycles: 4
 * bytes: 1
 */
static uint8_t rest_vec(uint8_t opcode, enum rst_vec vec)
{
    reg_value(pc) = vec;
    return cycles_table[opcode];
}

#define declare_rest_vec(_opcode, _vec)      \
    uint8_t opcode_##_opcode(uint8_t opcode) \
    {                                        \
        return rest_vec(opcode, _vec);       \
    }                                        \
    register_opcode_table(_opcode);

declare_rest_vec(0xc7, rst0);
declare_rest_vec(0xcf, rst1);
declare_rest_vec(0xd7, rst2);
declare_rest_vec(0xdf, rst3);
declare_rest_vec(0xe7, rst4);
declare_rest_vec(0xef, rst5);
declare_rest_vec(0xf7, rst6);
declare_rest_vec(0xff, rst7);