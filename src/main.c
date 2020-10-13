#include <stdio.h>
#include "../include/Stack.h"
#include "../include/Opcodes.h"

typedef unsigned char BYTE;

void load_rom(char*, BYTE*);

typedef struct {
	BYTE mem[0xFFF];
	BYTE V[0xF];
	unsigned int I = 0;
	unsigned int PC = 0;
	Stack stack;
} Chip8;

int main() {
	create_stack(16);

	Chip8 chip8;

	load_rom("../ROMS/BRIX", chip8.mem);
	return 0;
}

void load_rom(char* path_to_file, BYTE* mem) {
	FILE *fp = NULL;

	if ((fp = fopen(path_to_file, "r")) == NULL) {
		printf("ERROR: Cannot find file, unable to open!");
		return;
	}
	fp = fopen(path_to_file, "r");

	// Determines the size of the file
	fseek(fp, 0L, SEEK_END);
	unsigned int file_size = ftell(fp);
	rewind(fp);

	// Reads the file into memory starting at address 0x200
	fread(&mem[0x200], 1, file_size, fp);
}

BYTE read_opcode(Chip8 chip8) {
	unsigned int opcode = (chip8.mem[chip8.PC] << 8) | (chip8.mem[chip8.PC + 1]);
	execute_opcode(opcode, chip8);
	chip8.PC += 2;
}

//TODO Clean up to look more like this: initialize the Chip8, emulate a cycle (fetch, decode, execute), update timers, check if it needs to draw, check inputs