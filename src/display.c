#include "chip8.h"
#include "display.h"
#include "raylib.h"

void raylib_init() {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Chip-8 Interpreter");
	SetWindowMinSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTargetFPS(TARGET_FPS);

	BeginDrawing();
	ClearBackground(BLACK);
	EndDrawing();
}

bool should_exit() {
	return WindowShouldClose();
}

void close_display() {
	CloseWindow();
	return;
}

void draw_display(Chip8 *chip8) {
	// Pixels are represented by 10x10 sized rectangles
	uint8_t rect_width = CHIP8_DISPLAY_WIDTH / 64;
	uint8_t rect_height = CHIP8_DISPLAY_HEIGHT / 32;

	BeginDrawing();
	for (uint8_t row = 0; row < 32; row++) {
		for (uint8_t col = 0; col < 64; col++) {
			uint16_t x_pos = CHIP8_DISPLAY_X_OFFSET + col * rect_width;
			uint16_t y_pos = CHIP8_DISPLAY_Y_OFFSET + row * rect_height;
			if (chip8->display[row][col] == 1) {
				DrawRectangle(x_pos, y_pos, rect_width, rect_height, WHITE);
			}
		}
	}
	EndDrawing();
	return;
}