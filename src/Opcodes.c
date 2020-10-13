// TODO Create function to determine the opcode
// TODO Implement pointer functions so I don't need to use a long switch statement

void execute_opcode(unsigned int op, Chip8 chip8);

unsigned int nnn; // Lower 12 bits
unsigned int n; // Lower 4 bits
unsigned int x; // Lower 4 bits of high byte
unsigned int y; // Upper 4 bits of low byte
BYTE kk; // Lower byte

void execute_opcode(unsigned int op, Chip8 chip8) {
	nnn = op & 0x0FFF;
	n = op & 0x000F;
	x = op & 0x0F00;
	y = op & 0x00F0;
	kk = op & 0x00FF;

	opcode[op](chip8);
}

void opcode[0x0000](Chip8 chip8) {
	// Ignored by modern compilers
}

void opcode[0x00E0](Chip8 chip8) {
	//TODO Clear display
}

// Return from subroutine
void opcode[0x00EE](Chip8 chip8) {
	chip8.PC = chip8.stack.pop();
}

// Jump to address nnn
void opcode[0x1000](Chip8 chip8) {
	chip8.PC = nnn;
}
void opcode[0x00E0](Chip8 chip8) {

}
void opcode[0x00E0](Chip8 chip8) {

}
void opcode[0x00E0](Chip8 chip8) {

}
void opcode[0x00E0](Chip8 chip8) {

}
void opcode[0x00E0](Chip8 chip8) {

}
void opcode[0x00E0](Chip8 chip8) {

}
