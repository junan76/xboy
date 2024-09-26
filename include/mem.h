#ifndef MEM_H
#define MEM_H

#include <stdint.h>

struct MemRegion
{
    const char *name;
    uint16_t base;
    uint16_t size;
};

struct MemMapOps
{
    uint8_t (*read)(struct MemMap *mm, uint16_t addr);
    void (*write)(struct MemMap *mm, uint16_t addr, uint8_t val);
};

struct MemMap
{
    void *base;
    uint16_t total_size;

    struct MemRegion *regions;
    uint8_t n_regions;

    struct MemMapOps *ops;
};

#endif