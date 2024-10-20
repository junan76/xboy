#ifndef CPU_H
#define CPU_H

enum interrupt_source
{
    vblank_interrupt = 1,
    lcd_interrupt = 1 << 1,
    timer_interrupt = 1 << 2,
    serial_interrupt = 1 << 3,
    joypad_interrupt = 1 << 4,
};

int cpu_init();
uint8_t cpu_step();

uint8_t cpu_read_ie();
void cpu_write_ie(uint8_t value);

void cpu_pending_interrupt(enum interrupt_source int_source);

#endif