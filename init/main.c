#include <cpu.h>

int main(int argc, char const *argv[])
{
    int n = 7;
    while (n--)
    {
        cpu_step();
    }
    return 0;
}
