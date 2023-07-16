# Chip8
A basic Chip-8 interpreter written in C.

Technical reference: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

Projet is now functionally complete, although not perfect.

## Usage

To build, enter `make build`

To run the interpreter, enter `./chip8 <Path to ROM> <Speed (Hz)>`
Both the ROM and speed are optional, and defalt to BRIX and 540 respectively.

## Known Issues

The timing isn't perfect, which I think is causing some minor issues with collision detection.

There are minor issues with drawing to the display which may be caused by:
    - Bugs in ROMs used
    - Bugs with display opcode
    - Something else I haven't thought of

## Future

There are still several things I may add in the future if I return to this project:
    - Extend GUI to show the instructions being executed and the current register values
    - Use function pointers instead of switch statements
    - Change how GUI is handled, I think there is a better way