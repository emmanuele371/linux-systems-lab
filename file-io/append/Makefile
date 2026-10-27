CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -O2 -g

.PHONY: all clean

all: append

append: append.c
	$(CC) $(CFLAGS) -o append append.c

clean:
	rm -f append