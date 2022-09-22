#include "chip8.h"

// Fetch
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


// Decode/Execute