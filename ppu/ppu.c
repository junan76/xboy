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

static void inc_ly()
{
    ppu.lcd.status.ly += 1;

    if (ppu.lcd.status.ly == ppu.lcd.status.lyc)
    {
        ppu.lcd.status.stat.ly_eq_lyc = 1;
        if (ppu.lcd.status.stat.lyc_int)
            cpu_pending_interrupt(lcd_interrupt);
    }
}

static void reset_ly()
{
    ppu.lcd.status.ly = 0;

    if (ppu.lcd.status.ly == ppu.lcd.status.lyc)
    {
        ppu.lcd.status.stat.ly_eq_lyc = 1;
        if (ppu.lcd.status.stat.lyc_int)
            cpu_pending_interrupt(lcd_interrupt);
    }
}

void ppu_step(uint8_t cycles)
{
    /*update ppy mcycles*/
    ppu.mcycles += cycles;

    /*update ppu mode state machine*/
    switch (ppu.mode)
    {
    case oam_scan_mode: /*mode2 => mode3*/
        if (ppu.mcycles >= MCYCLES_OAM_SCAN_MODE)
            ppu.mode = drawing_mode;
        break;
    case drawing_mode: /*mode3 => mode0*/
        if (ppu.mcycles >= MCYCLES_OAM_SCAN_MODE + MCYCLES_DRAWING_MODE)
        {
            ppu.mode = hblank_mode;
            if (ppu.lcd.status.stat.hblank_int)
                cpu_pending_interrupt(lcd_interrupt);
        }
        break;
    case hblank_mode: /*mode0 => mode2/mode1*/
        if (ppu.mcycles >= MCYCLES_PER_LINE)
        {
            ppu.mcycles %= MCYCLES_PER_LINE;
            render_update_scanline(ppu.lcd.status.ly);

            if (ppu.lcd.status.ly < 143)
            {
                ppu.mode = oam_scan_mode;
                if (ppu.lcd.status.stat.oam_scan_int)
                    cpu_pending_interrupt(lcd_interrupt);
            }
            else
            {
                ppu.mode = vblank_mode;
                cpu_pending_interrupt(vblank_interrupt);
            }
            inc_ly();
        }
        break;
    case vblank_mode: /*mode1 => mode1/mode2*/
        if (ppu.mcycles >= MCYCLES_PER_LINE)
        {
            ppu.mcycles %= MCYCLES_PER_LINE;
            if (ppu.lcd.status.ly > 153)
            {
                render_update_screen();
                ppu.mode = oam_scan_mode;
                if (ppu.lcd.status.stat.oam_scan_int)
                    cpu_pending_interrupt(lcd_interrupt);
                reset_ly();
            }
            else
                inc_ly();
        }
        break;
    }

    /*update ppu_mode bits of lcd status register*/
    ppu.lcd.status.stat.ppu_mode = ppu.mode;
}

static uint8_t vram[8 * 1024];
static uint8_t oam[160];

struct PPU ppu = {
    .vram = vram,
    .oam = oam,
    .lcd = {
        .status = {
            .stat = {
                .ppu_mode = oam_scan_mode,
            },
        },
    },
};