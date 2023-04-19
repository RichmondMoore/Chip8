CC = gcc

CFLAGS = -Wall -Wextra -pedantic -std=c99
DEBUG = -g

OBJ_DIR = ./obj

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
LIBS = -lSDL2

$(info Source files: $(SRC))

all: chip8

debug: $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(DEBUG) $(LIBS) -o $@ $(OBJ)

chip8: $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $(OBJ)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean

clean:
	rm -f $(OBJ) chip8