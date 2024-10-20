add_library(ppu SHARED lcd.c object.c ppu.c render.c tile.c)
target_include_directories(ppu PUBLIC ../include)