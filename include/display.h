#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include <stdint.h>

#include "chip8.h"
#include "display.h"
#include "raylib.h"

// Defines

#define WINDOW_HEIGHT               (340)
#define WINDOW_WIDTH                (680)

#define CHIP8_DISPLAY_HEIGHT        (320)
#define CHIP8_DISPLAY_WIDTH         (640)

#define CHIP8_DISPLAY_X_OFFSET      (10)
#define CHIP8_DISPLAY_Y_OFFSET      (10)

// Functions

// display window
//  make border for display
//  add left panel for variable information
//  add right panel for executing instructions
// draw title above display

// draw display
// update left and right panels (separate functions)
// if in debug mode, show instructions

void raylib_init();
bool should_exit();
void close_display();
void draw_display(Chip8 *chip8);

#endif