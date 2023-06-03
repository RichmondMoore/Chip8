#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define DISPLAY_X       (640)
#define DISPLAY_Y       (320)

void init_display();
void cleanup_display();
void draw_to_display(uint8_t display[32][64]);
void clear_display();

#endif // DISPLAY_H