#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <xboy.h>

static void *load_cart_rom(const char *path, int *rom_size)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        log_err("%s: open %s failed", __func__, path);
        return NULL;
    }

    struct stat st;
    fstat(fd, &st);
    *rom_size = st.st_size;

    void *rom_data = mmap(NULL, *rom_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (rom_data == MAP_FAILED)
    {
        log_err("%s: mmap failed", __func__);
        return NULL;
    }
    close(fd);

    return rom_data;
}

int main(int argc, char const *argv[])
{
    int ret;

    void *rom_data;
    int rom_size;

    logger_set_level(LOG_LEVEL_DEBUG);

    rom_data = load_cart_rom(argv[1], &rom_size);
    ret = cart_init(rom_data, rom_size, NULL, 0);
    if (ret)
    {
        log_err("cart_init failed");
        return -1;
    }

    ret = cpu_init();
    if (ret)
    {
        log_err("cpu_init failed");
        return -1;
    }

    int n = 1;
    while (n--)
    {
        cpu_step();
    }
    

    return 0;
}
