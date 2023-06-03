#include "chip8.h"
#include "display.h"

int main() {
	// Initialize
	init_chip8();
	init_display();

	load_rom("../ROMS/Tests/4-flags.ch8");

	// Start loop
	bool quit = false;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					// keyboard[pressed key] = 1
					switch (event.key.type) {
						case SDLK_1:
							set_key(KEY_1);
							break;
						case SDLK_2:
							set_key(KEY_2);
							break;
						case SDLK_3:
							set_key(KEY_3);
							break;
						case SDLK_4:
							set_key(KEY_4);
							break;
						case SDLK_q:
							set_key(KEY_Q);
							break;
						case SDLK_w:
							set_key(KEY_W);
							break;
						case SDLK_e:
							set_key(KEY_E);
							break;
						case SDLK_r:
							set_key(KEY_R);
							break;
						case SDLK_a:
							set_key(KEY_A);
							break;
						case SDLK_s:
							set_key(KEY_S);
							break;
						case SDLK_d:
							set_key(KEY_D);
							break;
						case SDLK_f:
							set_key(KEY_F);
							break;
						case SDLK_z:
							set_key(KEY_Z);
							break;
						case SDLK_x:
							set_key(KEY_X);
							break;
						case SDLK_c:
							set_key(KEY_C);
							break;
						case SDLK_v:
							set_key(KEY_V);
							break;
						default:
							break;
					}
					break;
			}
		}

		cycle();
	}

	cleanup_display();

	return 0;
}