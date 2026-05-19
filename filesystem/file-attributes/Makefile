CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -D_DEFAULT_SOURCE
TARGETS = attrib

.PHONY: all clean

all: $(TARGETS)

attrib: attrib.c
	$(CC) $(CFLAGS) -o attrib attrib.c

clean:
	rm -f $(TARGETS) *.o
