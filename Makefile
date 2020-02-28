CFLAGS+= -g -Wall -Wextra -pedantic -std=c11


all: gameoflife.c gol.o gol.h
	gcc -g -o program gameoflife.c gol.o $(CFLAGS)
%.o: %.c
	gcc -c %.c $(CFLAGS)
clean:
	rm gol.o program

