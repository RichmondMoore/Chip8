#include "chip8.h"
#include "display.h"

int main() {
	// Initialize
	init_chip8();
	init_display();

	load_rom("../ROMS/Tests/3-corax+.ch8");

	// Start loop
	bool quit = false;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		cycle();
	}

	cleanup_display();

	return 0;
}