CC = gcc

CFLAGS = -Wall -Wextra -pedantic -std=c99
DEBUG = -g

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
LIBS = -lSDL2

$(info Source files: $(SRC))

all: chip8

debug: $(OBJ)
	$(CC) $(CFLAGS) $(DEBUG) $(LIBS) -o $@ $^

chip8: $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJ) chip8