cmake_minimum_required(VERSION 3.17)
include(pico_sdk_import.cmake)
set(ENV{PICO_SDK_PATH} D:/Projects/pico/pico-sdk/)

project(ina260 C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(ina260 main.cpp ina260.cpp ina260.h)
pico_sdk_init()

# Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(ina260 pico_stdlib hardware_i2c)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(ina260)
