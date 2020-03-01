#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"gol.h"

void read_in_file(FILE *infile, struct universe *u){
    u->width = -1;
    u->height = 0;
    u->grid = malloc(u->height * 512 * sizeof(char));
    char line[512] = "";
    while (fgets(line, 512, infile) != NULL){
        if (u->width == -1){
            u->width = sizeof(line);
        } else {
            if (sizeof(line)!= u->width){
                return;
            }
        }
        u->height++;
        u->grid = realloc(u->grid, u->height * 512 * sizeof(char));
        u->grid[u->height-1] = line;

    }

}
void write_out_file(FILE *outfile, struct universe *u){
    for (int i = 0; i < u->height; i++){
        for (int j = 0; j < u->width; j++){
            printf("%c", u->grid[i][j]);
        }
        printf("%c",'\n');
    }
}

int is_alive(struct universe *u, int column, int row){
    if (u->grid[row][column] == '.'){
        return 0;
    } else if (u->grid[row][column] == '*'){
        return 1;
    } else {
        return 0;
    }
}

int will_be_alive(struct universe *u, int column, int row){
    int one_left = column - 1;
    int one_right = column + 1;
    int one_up = row - 1;
    int one_down = row + 1;
    
    int column_1 = 1;
    int column_3 = 1;
    int row_1 = 1;
    int row_3 = 1;

    int alive = 0;

    if (one_left == -1){
        column_1 = 0;
    } else if (one_right == u->width){
        column_3 = 0;
    }

    if (one_up == -1){
        row_1 = 0;
    } else if (one_down == u->height){
        row_3 = 0;
    }

    int count = 0;


    /* Top Left */
    if (row_1 == 1 && column_1 == 1){
        if (is_alive(u, one_left, one_up)){
            count ++;
        }
    }

    /* Top Centre */
    if (row_1 == 1){
        if (is_alive(u, column, one_up)){
            count ++;
        }
    }
    /* Top Right */
    if (row_1 == 1 && column_3 == 1){
        if (is_alive(u, one_right, one_up)){
            count ++;
        }
    }
    /* Middle Left */
    if (column_1 == 1){
        if (is_alive(u, one_left, row)){
            count ++;
        }
    }
    /* Middle Right */
    if (column_3 == 1){
        if (is_alive(u, one_right, row)){
            count ++;
        }
    }
    /* Bottom Left */
    if (row_3 == 1 && column_1 == 1){
        if (is_alive(u, one_left, one_down)){
            count ++;
        }
    }
    /* Bottom Middle */
    if (row_3 == 1){
        if (is_alive(u, column, one_down)){
            count ++;
        }
    }
    /* Bottom Right */
    if (row_3 == 1 && column_3 == 1){
        if (is_alive(u, one_right, one_down)){
            count ++;
        }
    }

    if (count < 2) {alive = 0;} else if (count <= 3) {alive = 1;} else {alive = 0;}

    return alive;

}

int will_be_alive_torus(struct universe *u, int column, int row){


}

void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row)){
    
    
}

void print_statistics(struct universe *u){


}

