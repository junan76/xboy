#include <cpu.h>
#include <rom.h>

int main(int argc, char const *argv[])
{

    struct CartHeader *ch;
    int res;

    ch = rom_load_cart("./tests/roms/super-mario-land-world.gb");
    res = rom_check_cart((const struct CartHeader*)ch);

    int n = 7;
    while (n--)
    {
        cpu_step();
    }
    return 0;
}
