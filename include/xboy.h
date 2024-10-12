#ifndef XBOY_H
#define XBOY_H
#include <stdint.h>

/**
 * Cartridge
 */
int cart_init(void *rom_data, int rom_size, void *ram_data, int ram_size);

uint8_t cart_rom_read(uint16_t addr);
void cart_rom_write(uint16_t addr, uint8_t data);

uint8_t cart_ram_read(uint16_t addr);
void cart_ram_write(uint16_t addr, uint8_t data);

/**
 * Logger
 */
enum log_level
{
    LOG_LEVEL_MIN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_MAX,
};
void logger_set_level(int level);
void logging_with(int level, const char *fmt, ...);
#define log_err(fmt, args...) logging_with(LOG_LEVEL_ERROR, fmt, ##args)
#define log_warn(fmt, args...) logging_with(LOG_LEVEL_WARNING, fmt, ##args)
#define log_info(fmt, args...) logging_with(LOG_LEVEL_INFO, fmt, ##args)
#define log_debug(fmt, args...) logging_with(LOG_LEVEL_DEBUG, fmt, ##args)

#endif