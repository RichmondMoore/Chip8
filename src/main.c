#include "chip8.h"
#include "display.h"

int main() {
	// Initialize
	init_chip8();
	init_display();

	// Start loop
	bool quit = false;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	cleanup_display();

	return 0;
}