#include <xboy.h>

uint8_t bus_read(uint16_t addr)
{
    if (in_range(addr, ROM_BANK0_BASE, ROM_BANK1_BASE))
    {
        return cart_rom_read(addr);
    }
    else
    {
        log_warn("%s: read invalid addr=%x\n", __func__, addr);
        return 0xFF;
    }
}

void bus_write(uint16_t addr, uint8_t value)
{
}

int bus_init()
{

    return 0;
}