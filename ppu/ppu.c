#include <xboy.h>
#include "ppu-internal.h"

uint8_t ppu_vram_read(uint16_t addr)
{
}

void ppu_vram_write(uint16_t addr, uint8_t value)
{
}

uint8_t ppu_oam_read(uint16_t addr)
{
}

void ppu_oam_write(uint16_t addr, uint8_t value)
{
}

uint8_t ppu_io_read(uint16_t addr)
{
    if (addr == 0xFF46 || !in_range(addr, 0xFF40, 0xFF4C))
    {
        log_warn("%s: unsupported addr=0x%x", __func__, addr);
        return 0xFF;
    }

    switch (addr)
    {
    case 0xFF40:
        return ppu.lcd.control.val;
    case 0xFF41:
        return ppu.lcd.status.stat.val;
    case 0xFF42:
        return ppu.scrolling.scy;
    case 0xFF43:
        return ppu.scrolling.scx;
    case 0xFF44:
        return ppu.lcd.status.ly;
    case 0xFF45:
        return ppu.lcd.status.lyc;
    case 0xFF47:
        return ppu.pallete.bgp;
    case 0xFF48:
        return ppu.pallete.obp0;
    case 0xFF49:
        return ppu.pallete.obp1;
    case 0xFF4A:
        return ppu.scrolling.wy;
    case 0xFF4B:
        return ppu.scrolling.wx;
    }
}

void ppu_io_write(uint16_t addr, uint8_t value)
{
    if (addr == 0xFF46 || !in_range(addr, 0xFF40, 0xFF4C))
    {
        log_warn("%s: unsupported addr=0x%x", __func__, addr);
        return;
    }

    switch (addr)
    {
    case 0xFF40:
        ppu.lcd.control.val = value;
        return;
    case 0xFF41:
        /*lower 3 bits are read-only*/
        uint8_t lower3 = ppu.lcd.status.stat.val & 0x07;
        ppu.lcd.status.stat.val = (value & ~0x07);
        ppu.lcd.status.stat.val |= lower3;
        return;
    case 0xFF42:
        ppu.scrolling.scy = value;
        return;
    case 0xFF43:
        ppu.scrolling.scx = value;
        return;
    case 0xFF44:
        log_warn("%s: write to read-only addr=0x%x", addr);
        return;
    case 0xFF45:
        ppu.lcd.status.lyc = value;
        return;
    case 0xFF47:
        ppu.pallete.bgp = value;
        return;
    case 0xFF48:
        ppu.pallete.obp0 = value;
        return;
    case 0xFF49:
        ppu.pallete.obp1 = value;
        return;
    case 0xFF4A:
        ppu.scrolling.wy = value;
        return;
    case 0xFF4B:
        ppu.scrolling.wx = value;
        return;
    }
}

void ppu_step(uint8_t cycles)
{
}

struct PPU ppu;