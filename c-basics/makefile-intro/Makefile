CC = gcc
# flags + freestanding mode
CFLAGS = -W -Wall -Wextra -Werror -std=c18 -ffreestanding

TARGET = sum

# default target
.PHONY: all clean birne bsd doors

all:
	@echo "Bitte ein ziel angeben: birne, bsd oder doors."

birne: sum.c
	$(CC) $(CFLAGS) -DBIRNE_X sum.c -o $(TARGET)

bsd: sum.c
	$(CC) $(CFLAGS) -DLOCKED_BSE sum.c -o $(TARGET)

doors: sum.c
	$(CC) $(CFLAGS) -DDOORS_10 sum.c -o $(TARGET)

# clean build output
clean:
	rm -f $(TARGET)
