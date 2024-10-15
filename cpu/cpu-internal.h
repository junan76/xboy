#ifndef CPU_INTERNAL_H
#define CPU_INTERNAL_H

#include <stdio.h>
#include <stdint.h>

struct registers
{
    union
    {
        struct
        {
            union
            {
                uint8_t f;
                struct
                {
                    int __padding : 4;
                    int c_flag : 1;
                    int h_flag : 1;
                    int n_flag : 1;
                    int z_flag : 1;
                };
            };
            uint8_t a;
        };
        uint16_t af;
    };

    union
    {
        struct
        {
            uint8_t c;
            uint8_t b;
        };
        uint16_t bc;
    };

    union
    {
        struct
        {
            uint8_t e;
            uint8_t d;
        };
        uint16_t de;
    };

    union
    {
        struct
        {
            uint8_t l;
            uint8_t h;
        };
        uint16_t hl;
    };

    uint16_t sp;
    uint16_t pc;
};

struct CPU
{
    struct registers regs;

    struct
    {
        /*Interrupt master enable flag, internal to the CPU*/
        uint8_t ime;

        /*Interrupt enable register, address 0xFFFF*/
        union
        {
            uint8_t val;
            struct
            {
                uint8_t vblank : 1;
                uint8_t lcd : 1;
                uint8_t timer : 1;
                uint8_t serial : 1;
                uint8_t joypad : 1;
            };
        } ie;

        /*Interrupt flag register, address 0xFF0F*/
        union
        {
            uint8_t val;
            struct
            {
                uint8_t vblank : 1;
                uint8_t lcd : 1;
                uint8_t timer : 1;
                uint8_t serial : 1;
                uint8_t joypad : 1;
            };
        } iflag;
    } interrupts;

    uint8_t halted;
};

extern struct CPU cpu;
#define reg(r) &(cpu.regs.r)
#define reg_value(r) (cpu.regs.r)

typedef void (*opcode_fn)(uint8_t opcode);
extern opcode_fn opcode_table[256];
extern opcode_fn opcode_cb_table[256];

uint8_t read_byte_by_pc();
uint16_t read_word_by_pc();

#define register_opcode_table(_opcode)                                     \
    __attribute__((constructor)) static void opcode_##_opcode##_init(void) \
    {                                                                      \
        opcode_table[_opcode] = opcode_##_opcode;                          \
    }

#define carry_on_bit(bit, a, b) \
    ((a) + (b) & (1 << (bit) + 1) - 1) < ((a) & (1 << (bit) + 1) - 1)

#endif