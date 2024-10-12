#include <stdio.h>
#include <stdint.h>

/**
 * Memory map:
 * 0x0000 - 0x3FFF ROM Bank 0 (16KB)
 * 0x4000 - 0x7FFF ROM Bank 1-N (16KB)
 * 0xA000 - 0xBFFF External RAM from cartridge (if present) (8KB)
 *
 */

#define CART_ROM_BANK0_START 0x0000
#define CART_ROM_BANK0_END 0x3FFF
#define CART_ROM_BANK1_START 0x4000
#define CART_ROM_BANK1_END 0x7FFF
#define CART_RAM_BANK0_START 0xA000
#define CART_RAM_BANK0_END 0xBFFF

#define CART_ROM_BANK_SIZE 0x4000
#define CART_RAM_BANK_SIZE 0x2000

struct cart_header
{
    uint8_t entry[4];
    uint8_t logo[48];
    union
    {
        struct
        {
            union
            {
                char title[16];
                struct
                {
                    uint8_t __padding[11];
                    uint8_t manufacture[4];
                    uint8_t cgb_flag;
                };
            };

            uint8_t new_lic_code[2];
            uint8_t sgb_flag;
            /* MBC type, indicates how to handle the ROM and RAM banks */
            uint8_t cart_type;
            uint8_t rom_size;
            uint8_t ram_size;
            uint8_t dest_code;
            uint8_t old_lic_code;
            uint8_t version;
        };
        uint8_t raw_data[25];
    };
    uint8_t checksum;
    uint8_t global_chechsum;
};

/**
 * Cartridge structure
 *
 * rom: rom data
 * rom_bank0: always present
 * rom_bank1: present if any, can be switched
 *
 * ram: ram data
 * ram_bank0: present if any, can be switched
 */
struct cartridge
{
    struct cart_header *header;

    void *rom;
    void *rom_bank0;
    void *rom_bank1;

    void *ram;
    void *ram_bank0;

    uint8_t n_rom_bank;
    uint8_t n_ram_bank;
};

static struct cartridge cart;

uint8_t cart_rom_read(uint16_t addr)
{
    if (addr >= CART_ROM_BANK0_START && addr <= CART_ROM_BANK0_END)
        return ((uint8_t *)cart.rom_bank0)[addr - CART_ROM_BANK0_START];
    else if (addr >= CART_ROM_BANK1_START && addr <= CART_ROM_BANK1_END)
        return ((uint8_t *)cart.rom_bank1)[addr - CART_ROM_BANK1_START];
    else
    {
        // TODO:  error logging
        return 0xFF;
    }
}

void cart_rom_write(uint16_t addr, uint8_t data)
{
}

uint8_t cart_ram_read(uint16_t addr)
{
    if (addr >= CART_RAM_BANK0_START && addr <= CART_RAM_BANK0_END)
        return ((uint8_t *)cart.ram_bank0)[addr - CART_RAM_BANK0_START];
    else
    {
        // TODO:  error logging
        return 0xFF;
    }
}

void cart_ram_write(uint16_t addr, uint8_t data)
{
    if (addr >= CART_RAM_BANK0_START && addr <= CART_RAM_BANK0_END)
        ((uint8_t *)cart.ram_bank0)[addr - CART_RAM_BANK0_START] = data;
    else
    {
        // TODO:  error logging
    }
}

static int cart_header_checksum_ok(struct cart_header *header)
{
    uint8_t checksum = 0;
    for (int i = 0; i < 25; i++)
        checksum = checksum - header->raw_data[i] - 1;
    return checksum == header->checksum;
}

/**
 * Initialize the cartridge.
 *
 * @param rom_data ROM data.
 * @param rom_size ROM size in bytes.
 * @param ram_data RAM data.
 * @param ram_size RAM size in bytes
 */
int cart_init(void *rom_data, int rom_size, void *ram_data, int ram_size)
{

    int ret = 0;

    /* Check cartridge header. */
    struct cart_header *header = (struct cart_header *)(rom_data + 0x100);
    if (!cart_header_checksum_ok(header))
    {
        // TODO: error logging
        return -1;
    }

    /* Check rom_size and ram_size based on MBC type. */
    uint32_t rom_size_expected = 32 * 1024 * (1 << header->rom_size);
    uint32_t ram_size_expected = 0;
    switch (header->ram_size)
    {
    case 0x02:
        ram_size_expected = 8 * 1024;
        break;
    case 0x03:
        ram_size_expected = 32 * 1024;
        break;
    case 0x04:
        ram_size_expected = 128 * 1024;
        break;
    case 0x05:
        ram_size_expected = 64 * 1024;
        break;
    case 0x01:
    default:
        // TODO: error logging
        return -1;
    }

    if (rom_size != rom_size_expected || ram_size != ram_size_expected)
    {
        // TODO: error logging
        return -1;
    }

    // TODO: check rom_size and ram_size based on MBC type.

    /* Init cartridge. */
    cart.header = header;
    cart.rom = rom_data;
    cart.ram = ram_data;
    cart.n_rom_bank = rom_size / CART_ROM_BANK_SIZE;
    cart.n_ram_bank = ram_size / CART_RAM_BANK_SIZE;

    cart.rom_bank0 = cart.rom;
    if (cart.n_rom_bank > 1)
        cart.rom_bank1 = cart.rom + CART_ROM_BANK_SIZE;
    else
        cart.rom_bank1 = NULL;

    cart.ram_bank0 = cart.ram;

    // TODO: print cartridge information
    return 0;
}
