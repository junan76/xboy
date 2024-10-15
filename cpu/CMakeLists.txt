add_library(cpu SHARED cpu.c misc.c load8.c load16.c)
target_include_directories(cpu PRIVATE ../include)