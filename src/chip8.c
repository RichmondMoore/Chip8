#include "chip8.h"

void interpret() {
    Chip8 chip8;

    init_cpu(&chip8);
    init_display(&chip8);
    load_rom(&chip8, "ROMS/Tests/1-chip8-logo.ch8");
    load_fontset(&chip8);
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

    memset(&chip8->keyboard, 0, sizeof(chip8->keyboard)/sizeof(chip8->keyboard[0]));
}

void init_display(Chip8 *chip8) {
    memset(&chip8->display, 0, sizeof(chip8->display)/sizeof(chip8->display[0]));
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