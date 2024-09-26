#ifndef ROM_H
#define ROM_H

#include <stdint.h>

struct CartHeader
{
    uint8_t entry_point[4];
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

int rom_valid_cart(const struct CartHeader *ch);

#endif