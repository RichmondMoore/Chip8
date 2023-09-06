#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chip8.h"
#include "display.h"
#include "opcodes.h"

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

void run() {
    Chip8 chip8;

    init_cpu(&chip8);
    init_display(&chip8);
    //init_sound(&chip8);
    load_rom(&chip8, ROM_PATH);
    load_fontset(&chip8);

    while (!should_exit()) {
        // Allows program execution to stop
        // This will be set by a shortcut used for debugging
        if (chip8.halt) continue;

        // Clear display buffer
        //memset(chip8.display, 0, sizeof(chip8.display));

        // Handle user input
        set_keyboard(&chip8);

        // Get next opcode
        fetch(&chip8);

        // Execute instruction based on given opcode
        decode(&chip8);

        // Update the display
        draw_display(&chip8);
    }

    // Close display before exiting
    close_display();

    return;
}

void init_cpu(Chip8 *chip8) {
    chip8->I = 0;
    chip8->PC = 0x200;
    chip8->SP = 0;
    chip8->DT = 0;
    chip8->ST = 0;

    chip8->halt = false;
    chip8->wait_for_keypress = false;

    for (int i = 0; i < 16; i++) {
        chip8->V[i] = 0;
        chip8->stack[i] = 0;
    }

    memset(&chip8->keyboard, 0, sizeof(uint8_t) * sizeof(chip8->keyboard)/sizeof(chip8->keyboard[0]));
}

void init_display(Chip8 *chip8) {
    memset(&chip8->display, 0, sizeof(chip8->display));
    raylib_init();
}

/*void init_sound(Chip8 *chip8) {
    InitAudioDevice();
}*/

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
    chip8->PC += 2;
}

void decode(Chip8 *chip8) {
    uint16_t op = chip8->current_op;

	uint16_t nnn = op & 0x0FFF;
	uint8_t n = op & 0x000F;
	uint8_t x = (op >> 8) & 0x000F;
	uint8_t y = (op >> 4) & 0x000F;
	uint8_t kk = op & 0x00FF;

    switch (op & 0xF000) {
        case 0x0000:
            switch (op & 0x00FF) {
                case 0x00E0:
                    clear_screen(chip8);
                    break;
                case 0x00EE:
                    return_subroutine(chip8);
                    return;
                    break; // Unreachable
                default:
                    printf("ERROR: Unknown opcode %04X\n", op);
                    printf("Current PC: 0x%04X\n", chip8->PC);
                    exit(EXIT_FAILURE);
                    break; // Unreachable
            }
            break;
        case 0x1000:
            jump(chip8, nnn);
            return;
            break; // Unreachable
        case 0x2000:
            call_subroutine(chip8, nnn);
            return;
            break; // Unreachable
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
        case 0xE000:
            switch (op & 0x00FF) {
                case 0x9E:
                    skip_if_key_pressed(chip8, x);
                    break;
                case 0xA1:
                    skip_if_key_not_pressed(chip8, x);
                    break;
            }
            break;
        case 0xF000:
            switch (op & 0x00FF) {
                case 0x07:
                    set_reg_to_dt(chip8, x);
                    break;
                case 0x0A:
                    store_key_press(chip8, x);
                    break;
                case 0x15:
                    set_dt(chip8, x);
                    break;
                case 0x18:
                    set_st(chip8, x);
                    break;
                case 0x1E:
                    add_reg_to_i(chip8, x);
                    break;
                case 0x29:
                    load_sprite_address(chip8, x);
                    break;
                case 0x33:
                    store_bcd(chip8, x);
                    break;
                case 0x55:
                    store_regs(chip8, x);
                    break;
                case 0x65:
                    load_regs(chip8, x);
                    break;
            }
            break;
        default:
            exit(EXIT_FAILURE);
            break;
    }

    // Prevents PC from incrementing to next instruction until key is pressed
    if (chip8->wait_for_keypress) chip8->PC -= 2;
}

void set_keyboard(Chip8 *chip8) {
    if (IsKeyDown(KEY_ZERO)) chip8->keyboard[0x0] = true;
    else if (IsKeyDown(KEY_ONE)) chip8->keyboard[0x1] = true;
    else if (IsKeyDown(KEY_TWO)) chip8->keyboard[0x2] = true;
    else if (IsKeyDown(KEY_THREE)) chip8->keyboard[0x3] = true;
    else if (IsKeyDown(KEY_FOUR)) chip8->keyboard[0xC] = true;
    else if (IsKeyDown(KEY_Q)) chip8->keyboard[0x4] = true;
    else if (IsKeyDown(KEY_W)) chip8->keyboard[0x5] = true;
    else if (IsKeyDown(KEY_E)) chip8->keyboard[0x6] = true;
    else if (IsKeyDown(KEY_R)) chip8->keyboard[0xD] = true;
    else if (IsKeyDown(KEY_A)) chip8->keyboard[0x7] = true;
    else if (IsKeyDown(KEY_S)) chip8->keyboard[0x8] = true;
    else if (IsKeyDown(KEY_D)) chip8->keyboard[0x9] = true;
    else if (IsKeyDown(KEY_F)) chip8->keyboard[0xE] = true;
    else if (IsKeyDown(KEY_Z)) chip8->keyboard[0xA] = true;
    else if (IsKeyDown(KEY_X)) chip8->keyboard[0x0] = true;
    else if (IsKeyDown(KEY_C)) chip8->keyboard[0xB] = true;
    else if (IsKeyDown(KEY_V)) chip8->keyboard[0xF] = true;
    else if (IsKeyDown(KEY_SPACE)) chip8->halt = !chip8->halt; // Alternates to unhalt program

    return;
}

void decrement_timers(Chip8 *chip8) {
    if (chip8->DT > 0) chip8->DT--;
    if (chip8->ST > 0) {
        chip8->ST--;
        if (chip8->ST > 0) printf("beep!\n");
    }
}

// TODO move opcodes to new files: opcodes.c/.h
// TODO function to play sound
// TODO drop memset requirement
// TODO 'cleanup' function: free memory, unload audio, close display