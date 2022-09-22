#include <stdio.h>
#include "chip8.h"

int main() {
	load_rom("../ROMS/BRIX");

	for (int i = 0; i < 4096; i++) {
		printf("%d\n", mem[i]);
	}
	return 0;
}