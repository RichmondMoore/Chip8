#ifndef OPCODES_H
#define OPCODES_H

#include "chip8.h"

void clear_screen(Chip8 *chip8);
void return_subroutine(Chip8 *chip8);
void jump(Chip8 *chip8, uint16_t);
void call_subroutine(Chip8 *chip8, uint16_t nnn);
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
void skip_if_key_pressed(Chip8 *chip8, uint8_t x);
void skip_if_key_not_pressed(Chip8 *chip8, uint8_t x);
void set_reg_to_dt(Chip8 *chip8, uint8_t x);
void store_key_press(Chip8 *chip8, uint8_t x);
void set_dt(Chip8 *chip8, uint8_t x);
void set_st(Chip8 *chip8, uint8_t x);
void add_reg_to_i(Chip8 *chip8, uint8_t x);
void load_sprite_address(Chip8 *chip8, uint8_t x);
void store_bcd(Chip8 *chip8, uint8_t x);
void store_regs(Chip8 *chip8, uint8_t x);
void load_regs(Chip8 *chip8, uint8_t x);

#endif