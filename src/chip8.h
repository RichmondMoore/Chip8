#ifndef CHIP8_H
#define CHIP8_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// DEFINES

#define MEM_SIZE        (4096)


#define BYTE uint8_t

// VARIABLES

// Memory size: 4096 bytes
// 0x000-0x200 is reserved for the interpreter
// 0x200-0x600 is used for most Chip-8 programs
// 0x200-0xFFF program/data space
extern BYTE mem[MEM_SIZE];

// 16 general purpose registers V0-VF
// VF is used as a flag for certain instructions
extern BYTE V[16];
extern BYTE DT, ST; // Delay and sound timers
extern BYTE SP; // Stack pointer

extern uint16_t I; // Stores memory addresses
extern uint16_t PC; // Program counter
extern uint16_t stack[16];

extern BYTE display[32][64];

extern int misses;

// FUNCTIONS

void load_rom(char * path);
void init_chip8();
void init_display();
void cycle();
void draw_sprite();
BYTE rand_byte();

void print_misses();

#endif