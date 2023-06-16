#include "chip8.h"

int main(int argc, char *argv[]) {
	int instructions_per_second = 540;
	int count = 0;

	// Initialize
	init_chip8();
	init_display();

	if (argc >= 2) load_rom(argv[1]);
	else load_rom("../ROMS/Tests/6-keypad.ch8");

	if (argc == 3) instructions_per_second = atoi(argv[2]);

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
				printf("Pressed: %d\n", event.key.keysym.sym);
					switch (event.key.keysym.sym) {
						case SDLK_1:
							set_key(0x1, 1);
							break;
						case SDLK_2:
							set_key(0x2, 1);
							break;
						case SDLK_3:
							set_key(0x3, 1);
							break;
						case SDLK_4:
							set_key(0xC, 1);
							break;
						case SDLK_q:
							set_key(0x4, 1);
							break;
						case SDLK_w:
							set_key(0x5, 1);
							break;
						case SDLK_e:
							set_key(0x6, 1);
							break;
						case SDLK_r:
							set_key(0xD, 1);
							break;
						case SDLK_a:
							set_key(0x7, 1);
							break;
						case SDLK_s:
							set_key(0x8, 1);
							break;
						case SDLK_d:
							set_key(0x9, 1);
							break;
						case SDLK_f:
							set_key(0xE, 1);
							break;
						case SDLK_z:
							set_key(0x10, 1);
							break;
						case SDLK_x:
							set_key(0x0, 1);
							break;
						case SDLK_c:
							set_key(0xB, 1);
							break;
						case SDLK_v:
							set_key(0xF, 1);
							break;
						default:
							break;
					}
					break;
				case SDL_KEYUP:
					printf("Release: %d\n", event.key.keysym.sym);
					switch (event.key.keysym.sym) {
						case SDLK_1:
							set_key(0x1, 0);
							break;
						case SDLK_2:
							set_key(0x2, 0);
							break;
						case SDLK_3:
							set_key(0x3, 0);
							break;
						case SDLK_4:
							set_key(0xC, 0);
							break;
						case SDLK_q:
							set_key(0x4, 0);
							break;
						case SDLK_w:
							set_key(0x5, 0);
							break;
						case SDLK_e:
							set_key(0x6, 0);
							break;
						case SDLK_r:
							set_key(0xD, 0);
							break;
						case SDLK_a:
							set_key(0x7, 0);
							break;
						case SDLK_s:
							set_key(0x8, 0);
							break;
						case SDLK_d:
							set_key(0x9, 0);
							break;
						case SDLK_f:
							set_key(0xD, 0);
							break;
						case SDLK_z:
							set_key(0x10, 0);
							break;
						case SDLK_x:
							set_key(0x0, 0);
							break;
						case SDLK_c:
							set_key(0x11, 0);
							break;
						case SDLK_v:
							set_key(0xF, 0);
							break;
						default:
							break;
					}
			}
		}

		cycle();
		SDL_Delay((1000/instructions_per_second));
		count++;

		if (count == (instructions_per_second / 60)) {
			decrement_timers();
			count = 0;
		}
		
	}

	cleanup_display();

	return 0;
}