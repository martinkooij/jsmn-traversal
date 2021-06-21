# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(jtry C CXX ASM)

pico_sdk_init()

# Add executable. Default name is the project name, 
add_executable(jtry pico_example.cpp)
target_include_directories(jtry PRIVATE ../)

pico_enable_stdio_usb(jtry 1)
pico_enable_stdio_uart(jtry 0)

pico_add_extra_outputs(jtry)
target_link_libraries(jtry pico_stdlib)
