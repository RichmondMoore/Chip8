#include "chip8.h"

// Globals

uint8_t mem[MEM_SIZE];

uint8_t V[16];
uint8_t DT, ST; // Delay and sound timers
uint8_t SP; // Stack pointer

uint16_t I; // Stores memory addresses
uint16_t PC; // Program counter
uint16_t stack[16];

uint8_t display[32][64];

int misses;

unsigned char fontset[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0,  // 0
    0x20, 0x60, 0x20, 0x20, 0x70,  // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0,  // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0,  // 3
    0x90, 0x90, 0xF0, 0x10, 0x10,  // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0,  // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0,  // 6
    0xF0, 0x10, 0x20, 0x40, 0x40,  // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0,  // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0,  // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90,  // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0,  // B
    0xF0, 0x80, 0x80, 0x80, 0xF0,  // C
    0xE0, 0x90, 0x90, 0x90, 0xE0,  // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0,  // E
    0xF0, 0x80, 0xF0, 0x80, 0x80   // F
};

void load_rom(char * path) {
    FILE* fp;
    fp = fopen(path, "rb");

    if (!fp) {
        printf("ERROR: File cannot be opened");
    }

    // Skip to end of file and get file size
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET); // Go back to start of file

    fread(&mem[0x200], 1, fsize, fp); // Read contents of file into memory
    fclose(fp);
}

void init_chip8() {
	I = 0;
	PC = 0x200;

	misses = 0;

	for (int i = 0; i < 16; i++) {
		V[i] = 0;
		stack[i] = 0;
	}

	// Load fontset
	memcpy(&mem, &fontset, sizeof(fontset)/sizeof(uint8_t));

	// Allocate memory for display
	memset(display, 0, sizeof(display));
}

void cycle() {
	// Fetch
	uint16_t op = mem[PC] << 8 | mem[PC+1];
	uint16_t nnn = op & 0x0FFF;
	uint8_t n = op & 0x000F;
	uint8_t x = (uint8_t)(op & 0x0F00);
	uint8_t y = op & 0x00F0;
	uint8_t kk = op & 0x00FF;

	switch (op & 0xF000) {
		case 0x0000:
			switch (kk) {
				case 0x00E0:
					printf("CLS\n");
					memset(display, 0, sizeof(display));
					PC += 2;
					break;
				case 0x00EE:
					printf("RET\n");
					PC = stack[SP--];
					break;
				default:
					printf("ERROR: Unknown opcode %d", op);
			}
			break;
		case 0x1000:
			printf("JP %d\n", nnn);
			PC = nnn;
			break;
		case 0x2000:
			printf("CALL %d\n", nnn);
			stack[++SP] = PC;
			PC = nnn;
			break;
		case 0x3000:
			printf("SE V%d, %d\n", x, kk);
			PC += (V[x] == kk) ? 4 : 2;
			break;
		case 0x4000:
			printf("SNE V%d, %d\n", x, kk);
			PC += (V[x] != kk) ? 4 : 2;
			break;
		case 0x5000:
			printf("SE V%d, V%d\n", x, y);
			PC += (V[x] == V[y]) ? 4 : 2;
			break;
		case 0x6000:
			printf("LD V%d, %d\n", x, kk);
			V[x] = kk;
			PC += 2;
			break;
		case 0x7000:
			printf("ADD V%d, %d\n", x, kk);
			V[x] += kk;
			PC += 2;
			break;
		case 0x8000:
			switch (op & 0x000F) {
				case 0x0000:
					printf("LD V%d, V%d\n", x, y);
					V[x] = V[y];
					PC += 2;
					break;
				case 0x0001:
					printf("OR V%d, V%d\n", x, y);
					V[x] |= V[y];
					PC += 2;
					break;
				case 0x0002:
					printf("AND V%d, V%d\n", x, y);
					V[x] &= V[y];
					PC += 2;
					break;
				case 0x0003:
					printf("XOR V%d, V%d\n", x, y);
					V[x] ^= V[y];
					PC += 2;
					break;
				case 0x0004:
					printf("ADD V%d, V%d\n", x, y);
					V[x] += V[y];
					PC += 2;
					break;
				case 0x0005:
					printf("SUB V%d, V%d\n", x, y);
					V[0xF] = (V[x] > V[y]) ? 1 : 0;
					V[x] -= V[y];
					PC += 2;
					break;
				case 0x0006:
					printf("SHR V%d\n", x);
					V[0xF] = V[x] % 2;
					V[x] >>= 1;
					PC += 2;
					break;
				case 0x0007:
					printf("SUBN V%d, V%d\n", x, y);
					V[0xF] = (V[y] > V[x]) ? 1 : 0;
					V[x] = V[y] - V[x];
					PC += 2;
					break;
				case 0x000E:
					printf("SHL V%d\n", x);
					V[0xF] = V[x] >> 3;
					V[x] <<= 1;
					PC += 2;
					break;
				default:
					printf("ERROR: Unknown opcode %d\n", op);
					break;
			}
			break;
		case 0x9000:
			printf("SNE V%d, V%d\n", x, y);
			PC += (V[x] != V[y]) ? 4 : 2;
			break;
		case 0xA000:
			printf("LD I, %d\n", nnn);
			I = nnn;
			PC += 2;
			break;
		case 0xB000:
			printf("JP V0, %d\n", nnn);
			PC = V[0] + nnn;
			break;
		case 0xC000:
			printf("RND V%d, kk\n", x);
			V[x] = rand_uint8_t() & kk;
			PC += 2;
			break;
		case 0xD000:
			printf("DRW V%d, V%d, %d\n", x, y, n);
			// Read n uint8_ts starting at I, display at (Vx, Vy), VF = collision
			// Wrap around screen
			// Sprites are XORed onto the screen
			
			PC += 2;
			break;
		case 0xE000:
			switch (op & 0x00FF) {
				case 0x9E:
					printf("SKP Vx\n");
					PC += (1) ? 4 : 2; // TODO
					break;
				case 0xA1:
					printf("SKNP Vx\n");
					PC += (1) ? 2 : 4; // TODO
					break;
				default:
					printf("Unrecognized opcode.");
					misses++;
					break;
			}
			break;
		case 0xF000:
			switch (op & 0x00FF) {
				case 0x07:
					printf("LD Vx, DT\n");
					V[x] = DT;;
					PC += 2;
					break;
				case 0x0A:
					printf("LD Vx, K\n");
					// V[x] = K
					PC += 2;
					break;
				case 0x15:
					printf("LD DT, Vx\n");
					DT = V[x];
					PC += 2;
					break;
				case 0x18:
					printf("LD ST, Vx\n");
					ST = V[x];
					PC += 2;
					break;
				case 0x1E:
					printf("ADD I, Vx\n");
					I += V[x];
					PC += 2;
					break;
				case 0x29:
					printf("LD F, Vx\n");
					I = V[x] * 0x50;
					PC += 2;
					break;
				case 0x33:
					printf("LD B, Vx\n");
					mem[I] = V[x] / 100;
					mem[I + 1] = (V[x] / 10) % 10;
					mem[I + 2] = V[x] % 10;
					PC += 2;
					break;
				case 0x55:
					printf("LD [I], Vx\n");
					for (int i = 0; i < 15; i++) {
						mem[I + i] = V[i];
					}

					I += 16;
					PC += 2;
					break;
				case 0x65:
					printf("LD [I], Vx\n");
					for (int i = 0; i < 15; i++) {
						V[i] = mem[I + i];
					}

					I += 16;
					PC += 2;
					break;
			}
			break;
		default:
			printf("Not implemented yet.\n");
			misses++;
			break;
	}
}

uint8_t rand_uint8_t() {
	return rand() % 255;
}

void print_misses() {
	printf("Misses: %d\n", misses);
}