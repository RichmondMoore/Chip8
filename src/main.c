#include <stdio.h>
#include "chip8.h"

int main() {
	load_rom("../ROMS/BRIX");

	init_chip8();
	for (int i = 0; i < 500; i++)
		cycle();

	printf("Misses: %d", misses);
	return 0;
}