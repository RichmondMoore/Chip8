#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include "Stack.h"

typedef unsigned char BYTE;

typedef struct {
	BYTE mem[0xFFF];
	BYTE V[0xF];
	unsigned int I;
	unsigned int PC;
	Stack stack;
} Chip8;


#endif //CHIP8_CHIP8_H
