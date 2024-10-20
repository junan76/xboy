#include <xboy.h>
#include "cpu-internal.h"

enum irq_vec
{
    irq_vec_vblank = 0x40,
    irq_vec_lcd = 0x48,
    irq_vec_timer = 0x50,
    irq_vec_serial = 0x58,
    irq_vec_joypad = 0x60,
};

uint8_t read_byte_by_pc()
{
    uint16_t *pc = reg(pc);
    uint8_t result = bus_read(*pc);
    *pc += 1;
    return result;
}

uint16_t read_word_by_pc()
{
    uint16_t result = 0;
    uint16_t *pc = reg(pc);

    result = bus_read(*pc + 1) << 8 | bus_read(*pc);
    *pc += 2;

    return result;
}

uint8_t cpu_read_ie()
{
    return cpu.interrupts.ie.val;
}

void cpu_write_ie(uint8_t value)
{
    cpu.interrupts.ie.val = value;
}

static void cpu_push_pc()
{
    uint16_t pc = reg_value(pc);
    bus_write(--reg_value(sp), (pc >> 8) & 0xff);
    bus_write(--reg_value(sp), pc & 0xff);
}

static void handle_interrupt(enum irq_vec irq)
{
    /*Aknowledge the interrupt*/
    switch (irq)
    {
    case irq_vec_vblank:
        cpu.interrupts.iflag.vblank = 0;
        break;
    case irq_vec_lcd:
        cpu.interrupts.iflag.lcd = 0;
        break;
    case irq_vec_timer:
        cpu.interrupts.iflag.timer = 0;
        break;
    case irq_vec_serial:
        cpu.interrupts.iflag.serial = 0;
        break;
    case irq_vec_joypad:
        cpu.interrupts.iflag.joypad = 0;
        break;
    default:
        return;
    }

    /*Disable all interrupts*/
    cpu.interrupts.ime = 0;
    /*"STOP" instruction has different behaviors depends on the in_irq flag*/
    cpu.interrupts.in_irq = 1;
    /*Resume the cpu from halt mode*/
    cpu.halted = 0;

    /*Save pc, then jump to irq_vector*/
    cpu_push_pc();
    reg_value(pc) = irq;

    log_debug("handling interrupt: 0x%x", irq);
}

static void handle_interrupts()
{
    if (cpu.interrupts.ime == 0)
        return;

    /*Handle interrupt by priorities*/
    if (cpu.interrupts.ie.vblank && cpu.interrupts.iflag.vblank)
        handle_interrupt(irq_vec_vblank);
    else if (cpu.interrupts.ie.lcd && cpu.interrupts.iflag.lcd)
        handle_interrupt(irq_vec_lcd);
    else if (cpu.interrupts.ie.timer && cpu.interrupts.iflag.timer)
        handle_interrupt(irq_vec_timer);
    else if (cpu.interrupts.ie.serial && cpu.interrupts.iflag.serial)
        handle_interrupt(irq_vec_serial);
    else if (cpu.interrupts.ie.joypad && cpu.interrupts.iflag.joypad)
        handle_interrupt(irq_vec_joypad);
}

static uint8_t execute_instruction(uint8_t opcode)
{
    opcode_fn fn = opcode_table[opcode];
    return fn(opcode);
}

static void opcode_default(uint8_t opcode)
{
    log_err("unimplemented opcode: %x", opcode);
}

uint8_t cpu_step()
{
    handle_interrupts();

    if (cpu.halted)
    {
        if ((cpu.interrupts.ie.val & 0x1f) == 0)
            return 1;
        else
            cpu.halted = 0;
    }

    uint8_t opcode = read_byte_by_pc();
    uint8_t cycles = execute_instruction(opcode);
    cpu.mcycles += cycles;

    return cycles;
}

void cpu_pending_interrupt(enum interrupt_source int_source)
{
    int_source &= 0x1f;
    cpu.interrupts.iflag.val = int_source;
}

static uint8_t opcode_hole(uint8_t opcode)
{
    log_err("CPU panic: opcode 0x%x", opcode);
    return 0;
}

int cpu_init()
{
    /*Registers init.*/
    reg_value(pc) = 0x100;

    /*IME is unset by default.*/
    cpu.interrupts.ime = 0;
    cpu.interrupts.iflag.val = 0;
    cpu.interrupts.ie.val = 0;
    cpu.halted = 0;
    cpu.mcycles = 0;

    /*Init opcode holes*/
    uint8_t opcode_holes[] = {0xd3, 0xe3, 0xe4, 0xf4, 0xdb, 0xeb, 0xec, 0xfc, 0xdd, 0xed, 0xfd};
    for (int i = 0; i < sizeof(opcode_holes) / sizeof(opcode_holes[0]); i++)
        opcode_table[opcode_holes[i]] = opcode_hole;

    return 0;
}

struct CPU cpu;
opcode_fn opcode_table[256];
opcode_fn opcode_cb_table[256];

uint8_t cycles_table[256] = {
    1, 3, 2, 2, 1, 1, 2, 1, 5, 2, 2, 2, 1, 1, 2, 1, // 0x00 - 0x0F
    1, 3, 2, 2, 1, 1, 2, 1, 3, 2, 2, 2, 1, 1, 2, 1, // 0x10 - 0x1F
    2, 3, 2, 2, 1, 1, 2, 1, 2, 2, 2, 2, 1, 1, 2, 1, // 0x20 - 0x2F
    2, 3, 2, 2, 3, 3, 3, 1, 2, 2, 2, 2, 1, 1, 2, 1, // 0x30 - 0x3F
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 0x40 - 0x4F
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 0x50 - 0x5F
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 0x60 - 0x6F
    2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, // 0x70 - 0x7F
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 0x80 - 0x8F
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 0x90 - 0x9F
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 0xA0 - 0xAF
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 0xB0 - 0xBF
    2, 3, 3, 4, 3, 4, 2, 4, 2, 4, 3, 1, 3, 6, 2, 4, // 0xC0 - 0xCF
    2, 3, 3, 0, 3, 4, 2, 4, 2, 4, 3, 0, 3, 0, 2, 4, // 0xD0 - 0xDF
    3, 3, 2, 0, 0, 4, 2, 4, 4, 1, 4, 0, 0, 0, 2, 4, // 0xE0 - 0xEF
    3, 3, 2, 1, 0, 4, 2, 4, 3, 2, 4, 1, 0, 0, 2, 4, // 0xF0 - 0xFF
};

uint8_t cycles_cb_table[256] = {
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 0x00 - 0x0F
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 0x10 - 0x1F
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 0x20 - 0x2F
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 0x30 - 0x3F
    2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2, // 0x40 - 0x4F
    2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2, // 0x50 - 0x5F
    2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2, // 0x60 - 0x6F
    2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2, // 0x70 - 0x7F
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 0x80 - 0x0F
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 0x90 - 0x9F
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 0xA0 - 0xAF
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 0xB0 - 0xBF
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 0xC0 - 0xCF
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 0xD0 - 0xDF
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 0xE0 - 0xEF
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 0xF0 - 0xFF
};