#include "opcodes.h"

void clear_screen(Chip8 *chip8) {
    memset(chip8->display, 0, sizeof(chip8->display));
    return;
}

void return_subroutine(Chip8 *chip8) {
    chip8->PC = chip8->stack[chip8->SP - 1];
    chip8->SP--;
    return;
}

void jump(Chip8 *chip8, uint16_t nnn) {
    chip8->PC = nnn;
    return;
}

void call_subroutine(Chip8 *chip8, uint16_t nnn) {
    chip8->stack[chip8->SP++] = chip8->PC;
    chip8->PC = nnn;
    return;
}

void skip_if_equal(Chip8 *chip8, uint8_t x, uint8_t kk) {
    if (chip8->V[x] == kk) chip8->PC += 2;
    return;
}

void skip_if_not_equal(Chip8 *chip8, uint8_t x, uint8_t kk) {
    if (chip8->V[x] != kk) chip8->PC += 2;
    return;
}

void skip_if_regs_equal(Chip8 *chip8, uint8_t x, uint8_t y) {
    if (chip8->V[x] == chip8->V[y]) chip8->PC += 2;
    return;
}

void set_reg(Chip8 *chip8, uint8_t x, uint8_t kk) {
    chip8->V[x] = kk;
    return;
}

void add_imm_to_reg(Chip8 *chip8, uint8_t x, uint8_t kk) {
    chip8->V[x] += kk;
    return;
}

void set_reg_to_reg(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] = chip8->V[y];
    return;
}

void set_reg_or(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] |= chip8->V[y];
    return;
}

void set_reg_and(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] &= chip8->V[y];
    return;
}

void set_reg_xor(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] ^= chip8->V[y];
    return;
}

void add_regs(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] += chip8->V[y];
    chip8->V[0xF] = ((int) x + (int) y) > 255 ? 1 : 0;
    return;
}

void sub_regs(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] -= chip8->V[y];
    chip8->V[0xF] = (x > y) ? 1 : 0;
    return;
}

void shift_reg_right(Chip8 *chip8, uint8_t x) {
    chip8->V[x] = chip8->V[x] >> 1;
    chip8->V[0xF] = x & 0x1;
    return;
}

void sub_regs_reverse(Chip8 *chip8, uint8_t x, uint8_t y) {
    chip8->V[x] = chip8->V[y] - chip8->V[x];
    chip8->V[0xF] = (y > x) ? 1 : 0;
    return;
}

void shift_reg_left(Chip8 *chip8, uint8_t x) {
    chip8->V[x] = chip8->V[x] << 1;
    chip8->V[0xF] = (x >> 7) & 0x1;
    return;
}

void skip_if_regs_not_equal(Chip8 *chip8, uint8_t x, uint8_t y) {
    if (chip8->V[x] != chip8->V[y]) chip8->PC += 2;
    return;
}

void set_i(Chip8 *chip8, uint16_t nnn) {
    chip8->I = nnn;
    return;
}

void jump_indirect(Chip8 *chip8, uint16_t nnn) {
    chip8->PC = chip8->V[0] + nnn;
    return;
}

void set_reg_random(Chip8 *chip8, uint8_t x) {
    chip8->V[x] &= rand() % 255;
    return;
}

void draw(Chip8 *chip8, uint8_t x, uint8_t y, uint8_t n) {
    // Read n bytes of memory from I, at (Vx, Vy)
    // Xor onto screen, if pixel is erased, set Vf = 1

    // Display ref: [32][64]->[Y][X]
    chip8->V[0xF] = 0; // Preemptively set to 0

    // Wrap X and Y coords
    uint8_t X = chip8->V[x] % 64;
    uint8_t Y = chip8->V[y] % 32;

    for (uint8_t y_line = 0; y_line < n; y_line++) {
        uint8_t pixel = chip8->mem[chip8->I + y_line];

        for (uint8_t x_line = 0; x_line < 8; x_line++) {
            uint8_t bit = (pixel & (0x80 >> x_line));
            if (bit != 0) {
                if (chip8->display[Y + y_line][X + x_line] == 1) {
                    chip8->V[0xF] = 1;
                }
                chip8->display[Y + y_line][X + x_line] ^= 1;
            }
            if (X + x_line >= 64) break;
        }

        if (Y + y_line >= 32) break;
    }

    return;
}

void skip_if_key_pressed(Chip8 *chip8, uint8_t x) {
    if (chip8->keyboard[x] == true) chip8->PC += 2;
    return;
}

void skip_if_key_not_pressed(Chip8 *chip8, uint8_t x) {
    if (chip8->keyboard[x] != true) chip8->PC += 2;
    return;
}

void set_reg_to_dt(Chip8 *chip8, uint8_t x) {
    chip8->V[x] = chip8->DT;
    return;
}
void store_key_press(Chip8 *chip8, uint8_t x) {
    // Stop incrementing PC
    // Halts program until a key is pressed
    chip8->wait_for_keypress = true;
    for (uint8_t i = 0; i < 16; i++) {
        // Store the first key pressed
        if (chip8->keyboard[i] == true) {
            chip8->V[x] = i;
            chip8->wait_for_keypress = false; // Program can run now
        }
    }
    return;
}

void set_dt(Chip8 *chip8, uint8_t x) {
    chip8->DT = chip8->V[x];
    return;
}

void set_st(Chip8 *chip8, uint8_t x) {
    chip8->ST = chip8->V[x];
}

void add_reg_to_i(Chip8 *chip8, uint8_t x) {
    chip8->I += chip8->V[x];
    return;
}

void load_sprite_address(Chip8 *chip8, uint8_t x) {
    chip8->I = chip8->V[x] * 0x5;
    return;
}

void store_bcd(Chip8 *chip8, uint8_t x) {
    uint8_t val = chip8->V[x];

    chip8->mem[chip8->I + 2] = val % 10; val /= 10;
    chip8->mem[chip8->I + 1] = val % 10; val /= 10;
    chip8->mem[chip8->I] = val % 10;
    return;
}

void store_regs(Chip8 *chip8, uint8_t x) {
    for (uint8_t i = 0; i < x; i++) {
        chip8->mem[chip8->I + i] = chip8->V[i];
    }

    return;
}

void load_regs(Chip8 *chip8, uint8_t x) {
    for (uint8_t i = 0; i < x; i++) {
        chip8->V[i] = chip8->mem[chip8->I + i];
    }

    return;
}