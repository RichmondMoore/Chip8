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
    uint8_t draw_flag;

    uint8_t key_is_pressed;

    uint16_t current_op;
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

void run();
void init_cpu(Chip8 *chip8);
void init_display(Chip8 *chip8);
void load_rom(Chip8 *chip8, char *path);
void load_fontset(Chip8 *chip8);
void fetch(Chip8 *chip8);
void decode(Chip8 *chip8);

// Opcodes
void clear_screen(Chip8 *chip8);
void return_subroutine(Chip8 *chip8);
void jump(Chip8 *chip8, uint16_t);
void call_subroutine(Chip8 *chip8);
void skip_if_equal(Chip8 *chip8, uint8_t x, uint8_t kk);
void skip_if_not_equal(Chip8 *chip8, uint8_t x, uint8_t kk);
void skip_if_regs_equal(Chip8 *chip8, uint8_t x, uint8_t y);
void set_reg(Chip8 *chip8, uint8_t x, uint8_t kk);
void add_imm_to_reg(Chip8 *chip8, uint8_t x, uint8_t kk);
void set_reg_to_reg(Chip8 *chip8, uint8_t x, uint8_t y);
void set_reg_or(Chip8 *chip8, uint8_t x, uint8_t y);
void set_reg_and(Chip8 *chip8, uint8_t x, uint8_t y);
void set_reg_xor(Chip8 *chip8, uint8_t x, uint8_t y);
void add_regs(Chip8 *chip8, uint8_t x, uint8_t y);
void sub_regs(Chip8 *chip8, uint8_t x, uint8_t y);
void shift_reg_right(Chip8 *chip8, uint8_t x);
void sub_regs_reverse(Chip8 *chip8, uint8_t x, uint8_t y);
void shift_reg_left(Chip8 *chip8, uint8_t x);
void skip_if_regs_not_equal(Chip8 *chip8, uint8_t x, uint8_t y);
void set_i(Chip8 *chip8, uint16_t nnn);
void jump_indirect(Chip8 *chip8, uint16_t nnn);
void set_reg_random(Chip8 *chip8, uint8_t x);
void draw(Chip8 *chip8, uint8_t x, uint8_t y, uint8_t n);
void skip_if_key_presed(Chip8 *chip8);
void skip_if_key_not_pressed(Chip8 *chip8);
void set_reg_to_dt(Chip8 *chip8);
void store_key_press(Chip8 *chip8);
void set_dt(Chip8 *chip8);
void set_st(Chip8 *chip8);
void add_reg_to_i(Chip8 *chip8);
void load_sprite_address(Chip8 *chip8);
void store_bcd(Chip8 *chip8);
void store_regs(Chip8 *chip8);
void load_regs(Chip8 *chip8);

#endif