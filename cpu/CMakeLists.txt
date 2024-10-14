add_library(cpu STATIC cpu.c misc.c)
target_include_directories(cpu PRIVATE ../include)