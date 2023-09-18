# Chip8
A basic Chip-8 interpreter written in C.

Technical reference: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

Projet is now functionally complete, although not perfect.

## Usage

To build, enter `make build`, then run the executable `./chip8`

Note: I am planning to update the way ROMs and speeds are set, so the Usage instructions will change.

## Rewrite

This is my attempt at rewriting my Chip-8 emulator to be easier to work with, show more information, and fix underlying issues with my original implementation. This version uses Raylib rather than SDL2. Opcode execution is much more separated now, with each getting its own function rather than all of them being included in the giant switch statement.
