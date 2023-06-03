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
        -1, SDL_RENDERER_ACCELERATED);

    if (chip8_display->renderer == NULL) {
        printf("ERROR: Failed to create renderer, %s\n", SDL_GetError());
        exit(1);
    }


}

void cleanup_display() {
	SDL_DestroyWindow(chip8_display->window);
	SDL_Quit();
}

void draw_to_display(uint8_t display[32][64]) {
    SDL_SetRenderDrawColor(chip8_display->renderer, 0, 0, 0, 255);
    SDL_RenderClear(chip8_display->renderer);

    SDL_SetRenderDrawColor(chip8_display->renderer, 255, 255, 255, 255);
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 64; j++) {
            if (display[i][j] == 1) {
                // White pixel
                int rect_width = DISPLAY_X / 64;
                int rect_height = DISPLAY_Y / 32;

                SDL_Rect rect;
                rect.x = j * rect_width;
                rect.y = i * rect_height;
                rect.w = rect_width;
                rect.h = rect_height;
                SDL_RenderFillRect(chip8_display->renderer, &rect);
            }
        }
    }

    if (chip8_display->renderer == NULL) exit(1);

    SDL_RenderPresent(chip8_display->renderer);
}

void clear_display() {
    SDL_SetRenderDrawColor(chip8_display->renderer, 0, 0, 0, 255);
    SDL_RenderClear(chip8_display->renderer);
    SDL_RenderPresent(chip8_display->renderer);
}