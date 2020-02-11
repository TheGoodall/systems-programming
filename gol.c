#include<stdio.h>
#include<stdbool.h>
#include"gol.h"

void read_in_file(FILE *infile, struct universe *u){
    u->grid = malloc(1);
	int lines = 1;
	int lengthOfFirstLine = 0;
	char charBuffer;
	while (

}

void write_out_file(FILE *outfile, struct universe *u){

}

int is_alive(struct universe *u, int column, int row){

    return 1;

}

int will_be_alive(struct universe *u, int column, int row){


}

int will_be_alive_torus(struct universe *u, int column, int row){


}

void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row)){


}

void print_statistics(struct universe *u){


}

