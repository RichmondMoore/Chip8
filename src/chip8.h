#ifndef CHIP8_H
#define CHIP8_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "display.h"

// DEFINES

#define MEM_SIZE        (4096)

// VARIABLES

// Memory size: 4096 uint8_ts
// 0x000-0x200 is reserved for the interpreter
// 0x200-0x600 is used for most Chip-8 programs
// 0x200-0xFFF program/data space
extern uint8_t mem[MEM_SIZE];

// 16 general purpose registers V0-VF
// VF is used as a flag for certain instructions
extern uint8_t V[16];
extern uint8_t DT, ST; // Delay and sound timers
extern uint8_t SP; // Stack pointer

extern uint16_t I; // Stores memory addresses
extern uint16_t PC; // Program counter
extern uint16_t stack[16];

extern uint8_t display[32][64];

extern int misses;

// FUNCTIONS

void load_rom(char * path);
void init_chip8();
void cycle();

void draw_sprite();
bool Vx_pressed();
uint8_t rand_uint8_t();

void print_misses();

#endif