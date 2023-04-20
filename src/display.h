#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <SDL2/SDL.h>

#define DISPLAY_X       (640)
#define DISPLAY_Y       (320)

void init_display();
void cleanup_display();
void draw_to_display(uint8_t display[64][32]);

#endif // DISPLAY_H