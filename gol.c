#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"gol.h"
#include<string.h>

void read_in_file(FILE *infile, struct universe *u){
    u->width = -1;
    u->height = 0;
    u->grid = calloc(u->height, sizeof(char *));
    if (u->grid == NULL){
	    perror("Could not allocate memory");
	    exit(1);
    }
    u->generations = 0;
    u->average = 0;
    char line[514] = "\0";
    int linelength;
    char c[2];
    c[1] = '\0';

    while (1){
        linelength = 0;
        strcpy(line,  "\0");
        c[0] = fgetc(infile);
        
        do {
            strcat(line, &c[0]);
            linelength++;
            c[0] = fgetc(infile);
        } while (c[0] != '\n' && linelength <= 512 && c[0] != EOF);
        
        if (c[0] == EOF){
            break;
        }
        

        if (u->width == -1){
            u->width = linelength;
        } else {
            if (linelength!= u->width){
                return;
            }
        }
        u->height++;
        u->grid = realloc(u->grid, u->height * sizeof(char *));
	if(u->grid == NULL){
		perror("Could not allocate memory");
		exit(1);
	}
        u->grid[u->height-1] = calloc(u->width, sizeof(char));
	if (u->grid[u->height-1] == NULL){
		perror("Could not allocate memory");
		exit(1);
	}
        for (int i = 0; i< u->width; i++){
            if (line[i] == '*'){
                u->average++;
            }
            u->grid[u->height-1][i] = line[i];
            
        }


    }

}
void write_out_file(FILE *outfile, struct universe *u){
    for (int i = 0; i < u->height; i++){
        for (int j = 0; j<u->width; j++){
            putc(u->grid[i][j], outfile);
        }
        putc('\n', outfile);
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

    int alive = 0;
    
    
    if (is_alive(u, column, row)){
            if (count < 2) {alive = 0;} else if (count <= 3) {alive = 1;} 
    } else {
        if (count == 3){
            alive = 1;
        }
    }


    return alive;

}

int will_be_alive_torus(struct universe *u, int column, int row){

    int one_left = column - 1;
    int one_right = column + 1;
    int one_up = row - 1;
    int one_down = row + 1;
 
    if (one_left < 0){
        one_left = u->width-1;
    }
    if (one_right > u->width-1){
        one_right = 0;
    }
    if (one_up < 0){
        one_up = u->height-1;
    }
    if (one_down > u->height-1){
        one_down = 0;
    }

    int count = 0;

    if (is_alive(u, one_left,  one_up)){count += 1;}
    if (is_alive(u, column,    one_up)){count += 1;}
    if (is_alive(u, one_right, one_up)){count += 1;}
    if (is_alive(u, one_left,  row)){count += 1;}
    if (is_alive(u, one_right, row)){count += 1;}
    if (is_alive(u, one_left,  one_down)){count += 1;}
    if (is_alive(u, column,    one_down)){count += 1;}
    if (is_alive(u, one_right, one_down)){count += 1;}

    int alive = 0;
    
    
    if (is_alive(u, column, row)){
            if (count < 2) {alive = 0;} else if (count <= 3) {alive = 1;} 
    } else {
        if (count == 3){
            alive = 1;
        }
    }


    return alive;

}



void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row)){
    struct universe v;
    int alivecount = 0;
    v.height = u->height;
    v.width = u->width;
    v.grid = calloc(v.height, sizeof(char *));
    if (v.grid == NULL){
        perror("Failed to allocate Memory");
        exit(1);
    }
    for (int i=0; i<v.height; i++){
        v.grid[i] = calloc(v.width, sizeof(char));
        if (v.grid[i] == NULL){
            perror("Failed to allocate Memory");
            exit(1);
        }
        memcpy(v.grid[i], u->grid[i], v.width * sizeof(char));
    }
           
    for (int i = 0; i<u->height; i++){
        for (int j = 0; j< u->width; j++){
            if (rule(u, j, i)){
                v.grid[i][j] = '*';
                alivecount ++;
            } else {
                v.grid[i][j] = '.';
            }        
        }
    } 
    u->average = ((u->average * u->generations) + alivecount)/(u->generations+1);
    u->generations ++;
    u->alivecount = alivecount;
    for (int i = 0; i<v.height; i++){
        memcpy(u->grid[i], v.grid[i], v.width*sizeof(char));
        free(v.grid[i]);
    }
    free(v.grid);
    
}

void print_statistics(struct universe *u){
    double size = u->height * u->width;
    double alivepercent = (double)u->alivecount/size;
    double averagepercent = (double)u->average/size;
    printf("%3.3f%% of cells currently alive\n%3.3f%% of cells alive on average", alivepercent, averagepercent);
}

