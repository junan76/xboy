#include <xboy.h>

#define WRAM0_SIZE 4096
#define WRAM1_SIZE 4096
#define HRAM_SIZE 127

static uint8_t wram0[WRAM0_SIZE];
static uint8_t wram1[WRAM1_SIZE];
static uint8_t hram[HRAM_SIZE];

static uint8_t wram0_read(uint16_t addr)
{
    if (!in_range(addr, WRAM0_BASE, WRAM1_BASE))
    {
        log_warn("%s: addr=0x%x is not in range of [0x%x, 0x%x)", __func__, addr, WRAM0_BASE, WRAM1_BASE);
        return 0xFF;
    }

    return wram0[addr - WRAM0_BASE];
}

static void wram0_write(uint16_t addr, uint8_t value)
{
    if (!in_range(addr, WRAM0_BASE, WRAM1_BASE))
    {
        log_warn("%s: addr=0x%x is not in range of [0x%x, 0x%x)", __func__, addr, WRAM0_BASE, WRAM1_BASE);
        return;
    }

    wram0[addr - WRAM0_BASE] = value;
}

static uint8_t wram1_read(uint16_t addr)
{
    if (!in_range(addr, WRAM1_BASE, ECRAM_BASE))
    {
        log_warn("%s: addr=0x%x is not in range of [0x%x, 0x%x)", __func__, addr, WRAM1_BASE, ECRAM_BASE);
        return 0xFF;
    }

    return wram1[addr - WRAM1_BASE];
}

static void wram1_write(uint16_t addr, uint8_t value)
{
    if (!in_range(addr, WRAM1_BASE, ECRAM_BASE))
    {
        log_warn("%s: addr=0x%x is not in range of [0x%x, 0x%x)", __func__, addr, WRAM1_BASE, ECRAM_BASE);
        return;
    }

    wram1[addr - WRAM1_BASE] = value;
}

static uint8_t hram_read(uint16_t addr)
{
    if (!in_range(addr, HRAM_BASE, IE_REG_BASE))
    {
        log_warn("%s: addr=0x%x is not in range of [0x%x, 0x%x)", __func__, addr, HRAM_BASE, IE_REG_BASE);
        return 0xFF;
    }

    return hram[addr - HRAM_BASE];
}

static void hram_write(uint16_t addr, uint8_t value)
{
    if (!in_range(addr, HRAM_BASE, IE_REG_BASE))
    {
        log_warn("%s: addr=0x%x is not in range of [0x%x, 0x%x)", __func__, addr, HRAM_BASE, IE_REG_BASE);
        return;
    }

    hram[addr - HRAM_BASE] = value;
}

uint8_t bus_read(uint16_t addr)
{
    if (in_range(addr, ROM_BANK0_BASE, VRAM_BASE))
    {
        return cart_rom_read(addr);
    }
    else if (in_range(addr, VRAM_BASE, EXRAM_BASE))
    {
        // TODO: read vram from ppu
    }
    else if (in_range(addr, EXRAM_BASE, WRAM0_BASE))
    {
        return cart_ram_read(addr);
    }
    else if (in_range(addr, WRAM0_BASE, WRAM1_BASE))
    {
        return wram0_read(addr);
    }
    else if (in_range(addr, WRAM1_BASE, ECRAM_BASE))
    {
        return wram1_read(addr);
    }
    else if (in_range(addr, OAM_BASE, NORAM_BASE))
    {
        // TODO: read oam from ppu
    }
    else if (in_range(addr, IO_REG_BASE, HRAM_BASE))
    {
        // TODO: read io registers
    }
    else if (in_range(addr, HRAM_BASE, IE_REG_BASE))
    {
        // TODO: read hram
    }
    else if (addr = IE_REG_BASE)
    {
        // TODO: interrupt enable register
    }
    else
    {
        log_warn("%s: read invalid addr=%x\n", __func__, addr);
        return 0xFF;
    }
}

void bus_write(uint16_t addr, uint8_t value)
{
    if (in_range(addr, ROM_BANK0_BASE, VRAM_BASE))
    {
        cart_rom_write(addr, value);
    }
    else if (in_range(addr, VRAM_BASE, EXRAM_BASE))
    {
        // TODO: read vram from ppu
    }
    else if (in_range(addr, EXRAM_BASE, WRAM0_BASE))
    {
        cart_ram_write(addr, value);
    }
    else if (in_range(addr, WRAM0_BASE, WRAM1_BASE))
    {
        wram0_write(addr, value);
    }
    else if (in_range(addr, WRAM1_BASE, ECRAM_BASE))
    {
        wram1_write(addr, value);
    }
    else if (in_range(addr, OAM_BASE, NORAM_BASE))
    {
        // TODO: read oam from ppu
    }
    else if (in_range(addr, IO_REG_BASE, HRAM_BASE))
    {
        // TODO: read io registers
    }
    else if (in_range(addr, HRAM_BASE, IE_REG_BASE))
    {
        // TODO: read hram
    }
    else if (addr = IE_REG_BASE)
    {
        // TODO: interrupt enable register
    }
    else
    {
        log_warn("%s: read invalid addr=%x\n", __func__, addr);
    }
}

int bus_init()
{
    return 0;
}