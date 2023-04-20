#include "display.h"

struct SDL_display {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

struct SDL_display *chip8_display;

void init_display() {
    // Initialize chip8_display
    chip8_display = malloc(sizeof(struct SDL_display));
    if (chip8_display == NULL) {
        printf("ERROR: failed to allocate memory for struct display.\n");
        exit(1);
    }

    // Initialize SDL2
	SDL_Init(SDL_INIT_VIDEO);

	// Create window
	chip8_display->window = SDL_CreateWindow("Chip8",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		DISPLAY_X, DISPLAY_Y, SDL_WINDOW_SHOWN);

    if (chip8_display->window == NULL) {
        printf("ERROR: Failed to create window, %s\n", SDL_GetError());
        exit(1);
    }

    // Create renderer
    chip8_display->renderer = SDL_CreateRenderer(chip8_display->window,
        -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (chip8_display->renderer == NULL) {
        printf("ERROR: Failed to create renderer, %s\n", SDL_GetError());
        exit(1);
    }


}

void cleanup_display() {
    // Cleanup
	SDL_DestroyWindow(chip8_display->window);
	SDL_Quit();
}

void draw_to_display(uint8_t display[64][32]) {
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 32; j++) {
            if (display[i][j] == 1) {
                SDL_Rect rect = {i * 10, j * 10, 10, 10};
                SDL_renderFillRect(chip8_display->renderer, &rect);
            }
        }
    }
}