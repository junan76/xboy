#ifndef BUS_H
#define BUS_H

#include <stdint.h>

/**
 * 0x0000 /---------------------------------------------------------
 *        |
 *        |     ROM bank0 (16K from cart)
 *        |
 * 0x4000 |---------------------------------------------------------
 *        |
 *        |     ROM bank1~N (16K)
 *        |
 * 0x8000 |---------------------------------------------------------
 *        |
 *        |     Video RAM (VRAM, 8K)
 *        |
 * 0xA000 |---------------------------------------------------------
 *        |
 *        |     External RAM (EXRAM, 8K from cart if any)
 *        |
 * 0xC000 |---------------------------------------------------------
 *        |
 *        |     Work RAM (WRAM0, 4K)
 *        |
 * 0xD000 |---------------------------------------------------------
 *        |
 *        |     Work RAM (WRAM1, 4K, In CGB mode, switchable bank1~7)
 *        |
 * 0xE000 |---------------------------------------------------------
 *        |
 *        |     Echo RAM(ECRAM, NOT used)
 *        |
 * 0xFE00 |---------------------------------------------------------
 *        |
 *        |     Object Attribute Memory(OAM)
 *        |
 * 0xFEA0 |---------------------------------------------------------
 *        |
 *        |     NOT used
 *        |
 * 0xFF00 |---------------------------------------------------------
 *        |
 *        |     I/O Registers
 *        |
 * 0xFF80 |---------------------------------------------------------
 *        |
 *        |     High RAM(HRAM)
 *        |
 * 0xFFFF |---------------------------------------------------------
 *        |     Interrupt Enable Register
 *        \---------------------------------------------------------
 */

#define ROM_BANK0_BASE 0x0000
#define ROM_BANK1_BASE 0x4000
#define VRAM_BASE 0x8000
#define EXRAM_BASE 0xA000
#define WRAM0_BASE 0xC000
#define WRAM1_BASE 0xD000
#define ECRAM_BASE 0xE000
#define OAM_BASE 0xFE00
#define NORAM_BASE 0xFEA0
#define IO_REG_BASE 0xFF00
#define HRAM_BASE 0xFF80
#define IE_REG_BASE 0xFFFF

static inline int in_range(uint16_t addr, uint16_t start, uint16_t end)
{
    return addr >= start && addr < end;
}

int bus_init();

uint8_t bus_read(uint16_t addr);
void bus_write(uint16_t addr, uint8_t value);

#endif