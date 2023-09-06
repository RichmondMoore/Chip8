#ifndef CHIP8_H
#define CHIP8_H

#include "raylib.h"

#include <stdbool.h>
#include <stdint.h>

// DEFINES

#define MEM_SIZE        (4096)
#define ROM_PATH        ("ROMS/Tests/3-corax+.ch8")

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

    bool keyboard[16];

    uint16_t I; // Stores memory addresses
    uint16_t PC; // Program counter
    uint16_t stack[16];

    uint8_t display[32][64];

    bool halt;
    bool wait_for_keypress;

    Sound beep;

    uint16_t current_op;
} Chip8;

// FUNCTIONS

void run();
void init_cpu(Chip8 *chip8);
void init_display(Chip8 *chip8);
void init_sound(Chip8 *chip8);
void load_rom(Chip8 *chip8, char *path);
void load_fontset(Chip8 *chip8);
void fetch(Chip8 *chip8);
void decode(Chip8 *chip8);
void set_keyboard(Chip8 *chip8);
void decrement_timers(Chip8 *chip8);

#endif