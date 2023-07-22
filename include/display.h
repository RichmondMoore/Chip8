#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include <stdint.h>

#include "chip8.h"
#include "display.h"
#include "raylib.h"

// Defines

#define TARGET_FPS                  (10)

#define WINDOW_HEIGHT               (960)
#define WINDOW_WIDTH                (1920)

#define CHIP8_DISPLAY_HEIGHT        (640)
#define CHIP8_DISPLAY_WIDTH         (1280)

#define CHIP8_DISPLAY_X_OFFSET      ((WINDOW_WIDTH - CHIP8_DISPLAY_WIDTH) / 2)
#define CHIP8_DISPLAY_Y_OFFSET      ((WINDOW_HEIGHT - CHIP8_DISPLAY_HEIGHT) / 2)

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

// TODO make a window struct instead of using defines
//  this would allow more functions to control these parameters
//  instead of hard-coding them