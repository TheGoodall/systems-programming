#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include"gol.h"

void read_in_file(FILE *infile, struct universe *u){
    u->width = -1;
    u->height = 0;
    u->grid = malloc(u->height * sizeof(int*));
    char line[512] = "";
    while (fgets(line, 512, infile) != NULL){
        u->height++;
        u->grid = realloc(u->grid, u->height * sizeof(int));
        u->grid[u->height-1] = line;
        }
    }
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

