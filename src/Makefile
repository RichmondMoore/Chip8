CC = gcc

INC_DIR = ./include
CFLAGS = -Wall -Wextra -pedantic -std=c99 -I$(INC_DIR)
DEBUG = -g

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

$(info Source files: $(SRC))

all: chip8

debug: $(OBJ)
	$(CC) $(CFLAGS) $(DEBUG) -o $@ $^

chip8: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJ) chip8