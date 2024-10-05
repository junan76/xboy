#include <stdint.h>
#include "instructions.h"

declare_instruction(0x00, nop);

static struct Instruction *inst_main_table[] = {
    instruction_entry(0x00, nop),
};

static struct Instruction *inst_prefix_table[] = {

};

struct Instruction *parse_next_instruction(uint16_t pc)
{
    return inst_main_table[0];
}