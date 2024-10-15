add_library(cpu SHARED cpu.c misc.c load.c stack.c)
target_include_directories(cpu PRIVATE ../include)