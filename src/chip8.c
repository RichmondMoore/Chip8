#include "chip8.h"

// Globals

uint8_t mem[MEM_SIZE];

uint8_t V[16];
uint8_t DT, ST; // Delay and sound timers
uint8_t SP; // Stack pointer

uint8_t keyboard[16];

uint16_t I; // Stores memory addresses
uint16_t PC; // Program counter
uint16_t stack[16];

uint8_t display[32][64];

uint32_t cycle_count;

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

void load_rom(char *path) {
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
	SP = 0;

	misses = 0;

	cycle_count = 0;

	for (int i = 0; i < 16; i++) {
		V[i] = 0;
		stack[i] = 0;
	}

	// Load fontset data
	memcpy(&mem, fontset, sizeof(fontset)/sizeof(fontset[0]));

	// Allocate memory for display data
	memset(&display, 0, sizeof(display)/sizeof(display[0][0]));

	// Allocate memory for keyboard data
	memset(&keyboard, 0, sizeof(keyboard)/sizeof(keyboard[0]));
}

void cycle() {
	// Fetch
	uint16_t op = mem[PC] << 8 | mem[PC+1];
	uint16_t nnn = op & 0x0FFF;
	uint8_t n = op & 0x000F;
	uint8_t x = (op >> 8) & 0x000F;
	uint8_t y = (op >> 4) & 0x000F;
	uint8_t kk = op & 0x00FF;

	uint8_t x_val;
	uint8_t y_val;

	switch (op & 0xF000) {
		case 0x0000:
			switch (kk) {
				case 0x00E0:
					printf("CLS\n");
					clear_display();
					memset(display, 0, sizeof(display));
					PC += 2;
					break;
				case 0x00EE:
					printf("RET\n");
					PC = stack[--SP];
					break;
				default:
					printf("ERROR: Unknown opcode %d", op);
					PC += 2;
			}
			break;
		case 0x1000:
			printf("JP %d\n", nnn);
			PC = nnn;
			break;
		case 0x2000:
			printf("CALL %d\n", nnn);
			stack[SP++] = PC + 2;
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
		case 0x8000: // Arithmetic Instructions
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
					x_val = V[x];
					y_val = V[y];
					V[x] += V[y];
					V[0xF] = ((int) x_val + (int) y_val) > 255 ? 1 : 0;
					PC += 2;
					break;
				case 0x0005:
					printf("SUB V%d, V%d\n", x, y);
					x_val = V[x];
					y_val = V[y];
					V[x] -= V[y];
					V[0xF] = (x_val > y_val) ? 1 : 0;
					PC += 2;
					break;
				case 0x0006:
					printf("SHR V%d\n", x);
					x_val = V[x];
					V[x] = V[x] >> 1;
					V[0xF] = x_val & 0x1;
					PC += 2;
					break;
				case 0x0007:
					printf("SUBN V%d, V%d\n", x, y);
					x_val = V[x];
					y_val = V[y];
					V[x] = V[y] - V[x];
					V[0xF] = (y_val > x_val) ? 1 : 0;					
					PC += 2;
					break;
				case 0x000E:
					printf("SHL V%d\n", x);
					x_val = V[x];
					V[x] = V[x] << 1;
					V[0xF] = (x_val >> 7) & 0x1;
					PC += 2;
					break;
				default:
					printf("ERROR: Unknown opcode %d\n", op);
					PC += 2;
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
			V[0xF] = 0;
			uint8_t Y = V[y] % 32;
			uint8_t X = V[x] % 64;
			
			for (int y_line = 0; y_line < n; y_line++) {
				uint8_t pixel = mem[I + y_line];
				for (int x_line = 0; x_line < 8; x_line++) {
					uint8_t bit = (pixel & (0x80 >> x_line));
					if (bit != 0) {
						if (display[Y + y_line][X + x_line] == 1) {
							V[0xF] = 1;
						}

						display[Y + y_line][X + x_line] ^= 1;
					}
				}
			}

			draw_to_display(display);
			PC += 2;
			break;
		case 0xE000: // User Input Instructions
			switch (op & 0x00FF) {
				case 0x9E:
					printf("SKP Vx\n");
					PC += keyboard[V[x]] ? 4 : 2;
					break;
				case 0xA1:
					printf("SKNP Vx\n");
					PC += !keyboard[V[x]] ? 4 : 2;
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
					I = V[x] * 0x05;
					PC += 2;
					break;
				case 0x33:
					printf("LD B, Vx\n");
					uint8_t val = V[x];
					mem[I + 2] = val % 10; val /= 10;
					mem[I + 1] = val % 10; val /= 10;
					mem[I] = val % 10;
					PC += 2;
					break;
				case 0x55:
					printf("LD [I], Vx\n");
					for (int i = 0; i <= x; i++) {
						mem[I + i] = V[i];
					}

					PC += 2;
					break;
				case 0x65:
					printf("LD Vx, [I]\n");
					for (int i = 0; i <= x; i++) {
						V[i] = mem[I + i];
					}

					PC += 2;
					break;
			}
			break;
		default:
			printf("ERROR: Unknown opcode.\n");
			break;
	}
}

uint8_t rand_uint8_t() {
	return rand() % 255;
}

void set_key(uint8_t index) {
	keyboard[index] = 1;
}