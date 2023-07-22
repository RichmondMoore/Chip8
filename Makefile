CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -I$(INCLUDE_DIR) -L$(LIB_DIR)
#DEBUG = -ggdb

ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += -pg
endif

INCLUDE_DIR = ./include
LIB_DIR = ./lib
OBJ_DIR = ./src/obj

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRC))
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

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
$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Makes obj directory if it does not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)