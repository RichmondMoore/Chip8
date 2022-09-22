#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

// DEFINES

#define MEM_SIZE        (4096)


#define BYTE uint8_t

// VARIABLES

// Memory size: 4096 bytes
// 0x000-0x200 is reserved for the interpreter
// 0x200-0x600 is used for most Chip-8 programs
// 0x200-0xFFF program/data space
BYTE mem[MEM_SIZE];

// 16 general purpose registers V0-VF
// VF is used as a flag for certain instructions
BYTE V[16];
BYTE DT, ST; // Delay and sound timers
BYTE SP; // Stack pointer

uint16_t I; // Stores memory addresses
uint16_t PC; // Program counter
uint16_t stack[16];

BYTE display[32][64];

int misses;

// FUNCTIONS

void load_rom(char * path);
void init_chip8();
void cycle();
BYTE rand_byte();