CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -D_DEFAULT_SOURCE
TARGETS = ln

.PHONY: all clean

all: $(TARGETS)

ln: ln.c
	$(CC) $(CFLAGS) -o ln ln.c

clean:
	rm -f $(TARGETS) *.o
