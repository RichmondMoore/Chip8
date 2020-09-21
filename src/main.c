#include <stdio.h>
#include "../include/Stack.h"

typedef unsigned char BYTE;

void load_rom(char*, BYTE*);

typedef struct {
	BYTE mem[0xFFF];
	BYTE V[0xF];
	unsigned int I;
	unsigned int PC;
	Stack stack;
} Chip8;

int main() {
	create_stack(16);

	load_rom();
	return 0;
}

void load_rom(char* path_to_file, BYTE* mem) {
	FILE *fp = NULL;

}
