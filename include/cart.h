#ifndef CART_H
#define CART_H
#include <stdint.h>

int cart_init(void *rom_data, int rom_size, void *ram_data, int ram_size);

uint8_t cart_rom_read(uint16_t addr);
void cart_rom_write(uint16_t addr, uint8_t data);

uint8_t cart_ram_read(uint16_t addr);
void cart_ram_write(uint16_t addr, uint8_t data);

#endif