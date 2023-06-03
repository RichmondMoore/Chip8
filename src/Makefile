CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -std=c99
#DEBUG = -ggdb

ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += -g
endif

OBJ_DIR = ./obj

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
LIBS = -lSDL2

$(info Source files: $(SRC))
$(info LIBS: $(LIBS))

.PHONY: clean debug

# Builds chip8 executable (default)
all: chip8

clean:
	rm -f $(OBJ) chip8
	rm -f $(OBJ) debug

# Build executable with debug information
debug: clean $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

# Builds chip8 executable
chip8: $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

# Builds objects from source files
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Makes obj directory if it does not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)