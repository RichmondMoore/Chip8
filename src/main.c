#include "chip8.h"

int main() {
	load_rom("../ROMS/BRIX");

	init_chip8();
	for (int i = 0; i < 50000; i++)
		cycle();

	print_misses();
	return 0;
}