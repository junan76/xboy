#include <stdio.h>
#include <stdint.h>

#include <xboy.h>

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
    uint8_t ram_enabled;

    uint8_t n_rom_bank;
    uint8_t n_ram_bank;
};

static struct cartridge cart;

uint8_t cart_rom_read(uint16_t addr)
{
    if (in_range(addr, ROM_BANK0_BASE, ROM_BANK1_BASE))
    {
        return ((uint8_t *)cart.rom_bank0)[addr - ROM_BANK0_BASE];
    }
    else if (in_range(addr, ROM_BANK1_BASE, VRAM_BASE))
    {
        return ((uint8_t *)cart.rom_bank1)[addr - ROM_BANK1_BASE];
    }
    else
    {
        log_warn("%s: read invalid cart rom addr=0x%x", __func__, addr);
        return 0xFF;
    }
}

void cart_rom_write(uint16_t addr, uint8_t data)
{
}

uint8_t cart_ram_read(uint16_t addr)
{
    if (!cart.ram_enabled)
    {
        log_warn("%s: cart ram NOT enabled, addr=0x%x", addr);
        return 0xFF;
    }

    if (in_range(addr, EXRAM_BASE, WRAM0_BASE))
        return ((uint8_t *)cart.ram_bank0)[addr - EXRAM_BASE];
    else
    {
        log_warn("%s: read invalid cart ram addr=0x%x", __func__, addr);
        return 0xFF;
    }
}

void cart_ram_write(uint16_t addr, uint8_t data)
{
    if (in_range(addr, EXRAM_BASE, WRAM0_BASE))
        ((uint8_t *)cart.ram_bank0)[addr - EXRAM_BASE] = data;
    else
    {
        log_warn("%s: write to invalid cart ram addr=0x%x", addr);
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
        log_err("%s: invalid cart checksum", __func__);
        return -1;
    }

    /* Check rom_size and ram_size based on MBC type. */
    uint32_t rom_size_expected = 32 * 1024 * (1 << header->rom_size);
    uint32_t ram_size_expected;
    switch (header->ram_size)
    {
    case 0x00:
        ram_size_expected = 0;
        break;
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
        log_err("%s: header ram size(0x%x) not supported", __func__, header->ram_size);
        return -1;
    }

    if (rom_size != rom_size_expected || ram_size != ram_size_expected)
    {
        log_err("%s: rom_size=%d, rom_size_expected=%d", __func__, rom_size, rom_size_expected);
        log_err("%s: ram_size=%d, ram_size_expected=%d", __func__, ram_size, ram_size_expected);
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

    cart.ram_enabled = 0;
    cart.ram_bank0 = cart.ram;

    log_info("%s: done!\n"
             "Title: %s\n"
             "ROM bank num: %d\n"
             "RAM bank num: %d\n"
             "Checksum: 0x%x",
             __func__, header->title, cart.n_rom_bank, cart.n_ram_bank, header->checksum);
    return 0;
}
