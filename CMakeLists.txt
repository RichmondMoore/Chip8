cmake_minimum_required(VERSION 3.17)
project(Chip8 C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES
        include/*.h
        src/*.c)

add_executable(Chip8 ${SOURCES})