#ifndef CPU_H
#define CPU_H

int cpu_init();
int cpu_step();

uint8_t cpu_read_ie();
void cpu_write_ie(uint8_t value);

#endif