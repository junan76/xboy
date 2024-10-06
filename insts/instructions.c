#include <stdint.h>
#include "instructions.h"

/*misc instructions*/
declare_instruction(0x00, nop);

/*load instructions*/
/*ld b, r8*/
declare_instruction(0x40, ld);
declare_instruction(0x41, ld);
declare_instruction(0x42, ld);
declare_instruction(0x43, ld);
declare_instruction(0x44, ld);
declare_instruction(0x45, ld);
declare_instruction(0x47, ld);
/*ld c, r8*/
declare_instruction(0x48, ld);
declare_instruction(0x49, ld);
declare_instruction(0x4a, ld);
declare_instruction(0x4b, ld);
declare_instruction(0x4c, ld);
declare_instruction(0x4d, ld);
declare_instruction(0x4f, ld);
/*ld d, r8*/
declare_instruction(0x50, ld);
declare_instruction(0x51, ld);
declare_instruction(0x52, ld);
declare_instruction(0x53, ld);
declare_instruction(0x54, ld);
declare_instruction(0x55, ld);
declare_instruction(0x57, ld);
/*ld e, r8*/
declare_instruction(0x58, ld);
declare_instruction(0x59, ld);
declare_instruction(0x5a, ld);
declare_instruction(0x5b, ld);
declare_instruction(0x5c, ld);
declare_instruction(0x5d, ld);
declare_instruction(0x5f, ld);
/*ld h, r8*/
declare_instruction(0x60, ld);
declare_instruction(0x61, ld);
declare_instruction(0x62, ld);
declare_instruction(0x63, ld);
declare_instruction(0x64, ld);
declare_instruction(0x65, ld);
declare_instruction(0x67, ld);
/*ld l, r8*/
declare_instruction(0x68, ld);
declare_instruction(0x69, ld);
declare_instruction(0x6a, ld);
declare_instruction(0x6b, ld);
declare_instruction(0x6c, ld);
declare_instruction(0x6d, ld);
declare_instruction(0x6f, ld);
/*ld a, r8*/
declare_instruction(0x78, ld);
declare_instruction(0x79, ld);
declare_instruction(0x7a, ld);
declare_instruction(0x7b, ld);
declare_instruction(0x7c, ld);
declare_instruction(0x7d, ld);
declare_instruction(0x7f, ld);

static struct Instruction *inst_main_table[0xff] = {
    instruction_entry(0x00, nop),
    /*ld b, r8*/
    instruction_entry(0x40, ld),
    instruction_entry(0x41, ld),
    instruction_entry(0x42, ld),
    instruction_entry(0x43, ld),
    instruction_entry(0x44, ld),
    instruction_entry(0x45, ld),
    instruction_entry(0x47, ld),
    /*ld c, r8*/
    instruction_entry(0x48, ld),
    instruction_entry(0x49, ld),
    instruction_entry(0x4a, ld),
    instruction_entry(0x4b, ld),
    instruction_entry(0x4c, ld),
    instruction_entry(0x4d, ld),
    instruction_entry(0x4f, ld),
    /*ld d, r8*/
    instruction_entry(0x50, ld),
    instruction_entry(0x51, ld),
    instruction_entry(0x52, ld),
    instruction_entry(0x53, ld),
    instruction_entry(0x54, ld),
    instruction_entry(0x55, ld),
    instruction_entry(0x57, ld),
    /*ld e, r8*/
    instruction_entry(0x58, ld),
    instruction_entry(0x59, ld),
    instruction_entry(0x5a, ld),
    instruction_entry(0x5b, ld),
    instruction_entry(0x5c, ld),
    instruction_entry(0x5d, ld),
    instruction_entry(0x5f, ld),
    /*ld h, r8*/
    instruction_entry(0x60, ld),
    instruction_entry(0x61, ld),
    instruction_entry(0x62, ld),
    instruction_entry(0x63, ld),
    instruction_entry(0x64, ld),
    instruction_entry(0x65, ld),
    instruction_entry(0x67, ld),
    /*ld l, r8*/
    instruction_entry(0x68, ld),
    instruction_entry(0x69, ld),
    instruction_entry(0x6a, ld),
    instruction_entry(0x6b, ld),
    instruction_entry(0x6c, ld),
    instruction_entry(0x6d, ld),
    instruction_entry(0x6f, ld),
    /*ld a, r8*/
    instruction_entry(0x78, ld),
    instruction_entry(0x79, ld),
    instruction_entry(0x7a, ld),
    instruction_entry(0x7b, ld),
    instruction_entry(0x7c, ld),
    instruction_entry(0x7d, ld),
    instruction_entry(0x7f, ld),
};

static struct Instruction *inst_prefix_table[] = {

};

struct Instruction *parse_next_instruction(uint16_t pc)
{
    static int i = 0;
    static int opcodes[] = {0x00, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45};
    return inst_main_table[opcodes[i++]];
}