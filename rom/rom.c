#include <stdio.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <rom.h>

struct CartHeader *rom_load_cart(const char *rom_file)
{
    int fd = open(rom_file, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return NULL;
    }

    void *addr = mmap(NULL, 36 * 1024, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED)
    {
        perror("mmap");
        return NULL;
    }

    close(fd);
    return (struct CartHeader *)(addr + 0x100);
}

int rom_check_cart(const struct CartHeader *cart)
{
    return 0;
}