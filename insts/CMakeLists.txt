add_library(insts STATIC alu.c bit.c jump.c load.c misc.c stack.c instructions.c)
target_include_directories(insts PRIVATE ../include)