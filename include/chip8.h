#ifndef CHIP8_H
#define CHIP8_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// DEFINES

#define MEM_SIZE        (4096)

typedef struct {
    // Memory size: 4096 uint8_ts
    // 0x000-0x200 is reserved for the interpreter
    // 0x200-0x600 is used for most Chip-8 programs
    // 0x200-0xFFF program/data space
    uint8_t mem[MEM_SIZE];

    // 16 general purpose registers V0-VF
    // VF is used as a flag for certain instructions
    uint8_t V[16];
    uint8_t DT, ST; // Delay and sound timers
    uint8_t SP; // Stack pointer

    uint8_t keyboard[16];

    uint16_t I; // Stores memory addresses
    uint16_t PC; // Program counter
    uint16_t stack[16];

    uint8_t display[32][64];

    int misses;

    uint8_t key_is_pressed;


} Chip8;

uint8_t fontset[80] =  {
    0xF0, 0x90, 0x90, 0x90, 0xF0,  // 0
    0x20, 0x60, 0x20, 0x20, 0x70,  // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0,  // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0,  // 3
    0x90, 0x90, 0xF0, 0x10, 0x10,  // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0,  // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0,  // 6
    0xF0, 0x10, 0x20, 0x40, 0x40,  // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0,  // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0,  // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90,  // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0,  // B
    0xF0, 0x80, 0x80, 0x80, 0xF0,  // C
    0xE0, 0x90, 0x90, 0x90, 0xE0,  // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0,  // E
    0xF0, 0x80, 0xF0, 0x80, 0x80   // F
};

// FUNCTIONS

void interpret();
void init_cpu(Chip8 *chip8);
void init_display(Chip8 *chip8);
void load_rom(Chip8 *chip8, char *path);
void load_fontset(Chip8 *chip8);
void fetch(Chip8 *chip8);
void decode(Chip8 *chip8);

// Opcodes


#endif