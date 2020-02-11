all: gameoflife.c gol.o gol.h
	gcc -o program gameoflife.c gol.o
gol.o: gol.c gol.h
	gcc -c gol.c
clean:
	rm gol.o program

