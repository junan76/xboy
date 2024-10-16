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

static void execute_instruction(uint8_t opcode)
{
    opcode_fn fn = opcode_table[opcode];
    fn(opcode);
}

static void opcode_default(uint8_t opcode)
{
    log_err("unimplemented opcode: %x", opcode);
}

int cpu_step()
{
    handle_interrupts();
    if (cpu.halted)
        return 0;

    uint8_t opcode = read_byte_by_pc();
    execute_instruction(opcode);
}

int cpu_init()
{
    /*Registers init.*/
    reg_value(pc) = 0x100;

    /*IME is unset by default.*/
    cpu.interrupts.ime = 0;
    cpu.interrupts.iflag.val = 0;
    cpu.interrupts.ie.val = 0;

    return 0;
}

struct CPU cpu;
opcode_fn opcode_table[256];
opcode_fn opcode_cb_table[256];
uint8_t cycles_table[256];
uint8_t cycles_cb_table[256];