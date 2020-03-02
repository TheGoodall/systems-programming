CFLAGS+= -g -Wall -Wextra -pedantic -std=c11


all: gameoflife.c gol.o gol.h
	gcc -g -o gameoflife gameoflife.c gol.o $(CFLAGS)
gol.o: gol.c
	gcc -c gol.c $(CFLAGS)
clean:
	rm gol.o gameoflife

