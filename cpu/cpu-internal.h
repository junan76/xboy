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
};

extern struct CPU cpu;
#define reg(r) &(cpu.regs.r)
#define reg_value(r) (cpu.regs.r)

typedef void (*opcode_fn)(uint8_t opcode);
extern opcode_fn opcode_table[256];

/**
 * Instruction block initialization.
 */
void misc_init();

#endif