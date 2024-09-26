#ifndef CPU_H
#define CPU_H

#include <stdint.h>

enum FlagBits
{
    c = (1 << 4), /* carry flag */
    h = (1 << 5), /* half carray flag */
    n = (1 << 6), /* subtraction flag */
    z = (1 << 7), /* zero flag */
};

struct Registers
{
    union
    {
        uint16_t af;
        struct
        {
            uint8_t __padding;
            uint8_t a;
        };
    };
    union
    {
        uint16_t bc;
        struct
        {
            uint8_t c;
            uint8_t b;
        };
    };
    union
    {
        uint16_t de;
        struct
        {
            uint8_t e;
            uint8_t d;
        };
    };
    union
    {
        uint16_t hl;
        struct
        {
            uint8_t l;
            uint8_t h;
        };
    };
    uint8_t flags;
    uint16_t sp;
    uint16_t pc;
};

struct CpuOps
{
    struct Instruction *(*fetch)(void);
    void (*execute)(void);
};

struct Cpu
{
    struct Registers regs;
    struct MemMap *mm;

    struct CpuOps *ops;
};

#endif