add_library(cpu SHARED cpu.c misc.c load8.c load16.c branch.c bit.c arithlogic8.c)
target_include_directories(cpu PRIVATE ../include)