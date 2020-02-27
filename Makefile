all: gameoflife.c gol.o gol.h
	gcc -o program gameoflife.c gol.o -Wall -Wextra -pedantic -std=c11
gol.o: gol.c gol.h
	gcc -c gol.c -Wall -Wextra -pedantic -std=c11
clean:
	rm gol.o program

