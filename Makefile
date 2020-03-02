CFLAGS+= -g -Wall -Wextra -pedantic -std=c11


all: gameoflife.c gol.o gol.h libgol.so 
	gcc -g -o gameoflife gameoflife.c gol.o $(CFLAGS)
gol.o: gol.c
	gcc -c -fPIC gol.c $(CFLAGS)
libgol.so: gol.o
	gcc gol.o -shared -o libgol.so $(CFLAGS)
clean:
	rm gol.o gameoflife libgol.so

