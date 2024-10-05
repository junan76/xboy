#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#define __register_instruction(_opcode, _opname, _op1, _op2, _cycles, _execution_fn) \
    struct Instruction inst_##_opname##_##_opcode =                                  \
        {                                                                            \
            .opcode = _opcode,                                                       \
            .op1 = _op1,                                                             \
            .op2 = _op2,                                                             \
            .n_cycles = _cycles,                                                     \
            .execute = _execution_fn,                                                \
    };

#define instruction_entry(opcode, opname) \
    [opcode] = &inst_##opname##_##opcode

#define declare_instruction(opcode, opname) \
    extern struct Instruction inst_##opname##_##opcode

#endif