#include "chip8.h"
#include "display.h"

void run() {
    Chip8 chip8;

    init_cpu(&chip8);
    init_display(&chip8);
    load_rom(&chip8, "ROMS/Tests/1-chip8-logo.ch8");
    load_fontset(&chip8);

    while (1) {
        fetch(&chip8);
        decode(&chip8);

        if (chip8.draw_flag) {
            // Call to display.c function
        }
    }
}

void init_cpu(Chip8 *chip8) {
    chip8->I = 0;
    chip8->PC = 0x200;
    chip8->SP = 0;
    chip8->DT = 0;
    chip8->ST = 0;

    for (int i = 0; i < 16; i++) {
        chip8->V[i] = 0;
        chip8->stack[i] = 0;
    }

    memset(&chip8->keyboard, 0, sizeof(uint8_t) * sizeof(chip8->keyboard)/sizeof(chip8->keyboard[0]));
}

void init_display(Chip8 *chip8) {
    memset(&chip8->display, 0, sizeof(chip8->display)/sizeof(chip8->display[0]));
    raylib_init();
}

void load_rom(Chip8 *chip8, char *path) {
    FILE* fp;
    fp = fopen(path, "rb");

    if (!fp) {
        printf("ERROR: File cannot be opened");
    }

    // Skip to end of file and get file size
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET); // Go back to start of file

    fread(&chip8->mem[0x200], 1, fsize, fp); // Read contents of file into memory
    fclose(fp);
}

void load_fontset(Chip8 *chip8) {
    memcpy(&chip8->mem, fontset, sizeof(fontset)/sizeof(fontset[0]));
}

void fetch(Chip8 *chip8) {
    chip8->current_op = chip8->mem[chip8->PC] << 8 | chip8->mem[chip8->PC + 1];
}

void decode(Chip8 *chip8) {
    uint16_t op = chip8->current_op;

	uint16_t nnn = op & 0x0FFF;
	uint8_t n = op & 0x000F;
	uint8_t x = (op >> 8) & 0x000F;
	uint8_t y = (op >> 4) & 0x000F;
	uint8_t kk = op & 0x00FF;

    switch (chip8->current_op & 0xF000) {
        case 0x0000:
            switch (op & 0x00FF) {
                case 0x00E0:
                    clear_screen(chip8);
                    break;
                case 0x00EE:
                    return_subroutine(chip8);
                    break;
                default:
                    printf("ERROR: Unknown opcode %04X\n", op);
            }
            break;
        case 0x1000:
            jump(chip8, nnn);
            break;
        case 0x2000:
            call_subroutine(chip8);
            break;
        case 0x3000:
            skip_if_equal(chip8, x, kk);
            break;
        case 0x4000:
            skip_if_not_equal(chip8, x, kk);
            break;
        case 0x5000:
            skip_if_regs_equal(chip8, x, y);
            break;
        case 0x6000:
            set_reg(chip8, x, kk);
            break;
        case 0x7000:
            add_imm_to_reg(chip8,x, kk);
            break;
        case 0x8000:
            switch (op & 0x000F) {
                case 0x000:
                    set_reg_to_reg(chip8, x, y);
                    break;
                case 0x001:
                    set_reg_or(chip8, x, y);
                    break;
                case 0x002:
                    set_reg_and(chip8, x, y);
                    break;
                case 0x003:
                    set_reg_xor(chip8, x, y);
                    break;
                case 0x004:
                    add_regs(chip8, x, y);
                    break;
                case 0x005:
                    sub_regs(chip8, x, y);
                    break;
                case 0x006:
                    shift_reg_right(chip8, x);
                    break;
                case 0x007:
                    sub_regs_reverse(chip8, x, y);
                    break;
                case 0x00E:
                    shift_reg_left(chip8, x);
                    break;
            }
            break;
        case 0x9000:
            skip_if_regs_not_equal(chip8, x, y);
            break;
        case 0xA000:
            set_i(chip8, nnn);
            break;
        case 0xB000:
            jump_indirect(chip8, nnn);
            break;
        case 0xC000:
            set_reg_random(chip8, x);
            break;
        case 0xD000:
            draw(chip8, x, y, n);
            break;
        default:
            break;
    }

    chip8->PC += 2;
}

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

void call_subroutine(Chip8 *chip8) {
    chip8->stack[chip8->SP++] = chip8->PC + 2;
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
    chip8->V[x] = rand() % 255;
}

void draw(Chip8 *chip8, uint8_t x, uint8_t y, uint8_t n) {
    // Read n bytes of memory from I, at (Vx, Vy)
    // Xor onto screen, if pixel is erased, set Vf = 1
    // Wrap around screen

    // Display ref: [32][64]->[Y][X]
    chip8->V[0xF] = 0; // Preemptively set to 0

    // Wrap X and Y coords
    uint8_t X = chip8->V[x] % 64;
    uint8_t Y = chip8->V[y] % 32;

    uint8_t pixel_count = 0;

    for (uint8_t y_line = 0; pixel_count < n; y_line++) {
        uint8_t pixel = chip8->mem[chip8->I + y_line];
        pixel_count++;

        for (uint8_t x_line = 0; x_line < 8; x_line++) {
            uint8_t bit = (pixel & (0x80 >> x_line));
            if (bit != 0) {
                if (chip8->display[Y + y_line][X + x_line] == 1) {
                    chip8->V[0xF] = 1;
                }
                chip8->display[Y + y_line][X + x_line] ^= 1;
            }
        }
    }

    chip8->draw_flag = 1;
}

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