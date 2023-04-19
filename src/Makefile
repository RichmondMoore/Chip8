CC = gcc

CFLAGS = -Wall -Wextra -pedantic -std=c99
DEBUG = -g

OBJ_DIR = ./obj

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
LIBS = -lSDL2

$(info Source files: $(SRC))

# Builds chip8 executable (default)
all: chip8

# Build executable with debug information
debug: $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(DEBUG) $(LIBS) -o $@ $(OBJ)

# Builds chip8 executable
chip8: $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $(OBJ)

# Builds objects from source files
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Makes obj directory if it does not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean

clean:
	rm -f $(OBJ) chip8