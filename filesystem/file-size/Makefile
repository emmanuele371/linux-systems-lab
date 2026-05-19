CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -D_DEFAULT_SOURCE
TARGETS = size

.PHONY: all clean

all: $(TARGETS)

size: size.c
	$(CC) $(CFLAGS) -o size size.c

clean:
	rm -f $(TARGETS) *.o
