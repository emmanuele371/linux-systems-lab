CFLAGS += -W -Wall -Wextra -Werror

all: foo bar

foo: foo.o
	gcc $(CFLAGS) foo.o -o foo

foo.o: foo.c
	gcc -c foo.c

bar: bar.o
	gcc $(CFLAGS) bar.o -o bar

bar.o: bar.c
	gcc -c bar.c


.PHONY: clean

clean: rm -f *.o foo bar
