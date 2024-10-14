cmake_minimum_required(VERSION 3.27..3.30)
project(xboy LANGUAGES C)

add_executable(xboy init/main.c)
add_subdirectory(cartridge)
add_subdirectory(cpu)
add_subdirectory(bus)
add_subdirectory(utils)

# target_include_directories(xboy PRIVATE include)
target_link_libraries(xboy PRIVATE cartridge cpu bus utils)