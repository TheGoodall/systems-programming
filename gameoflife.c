#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"gol.h"
int main(int argc, char *argv[]){
  
    FILE *infile = stdin;  
    char* infilename = NULL;
    FILE *outfile = stdout;
    char* outfilename = NULL;

    int generations = 5;

    int printStats = 0;
    int torus = 0;

    char* argument;
    if (argc > 1){
        for (int i = 1; i<argc; i++){
            argument = argv[i];
            switch(argument[1]){
                case 'i':
                    i++;
                    if (i<=argc){
                        infilename = argv[i];
                    } else {exit(1);}
                    break;
                case 'o':
                    i++;
                    if (i<=argc){
                        outfilename = argv[i];
                    } else {exit(1);}
                    break;
                case 'g':
                    i++;
                    if (i<=argc){
                        generations = (int)atoi(argv[i]);
                    } else {exit(1);}
                    break;
                case 's':
                    printStats = 1;
                    break;
                case 't':
                    torus = 1;
                    break;
                default:
                    exit(1);
                    break;
            }
            

        }
    }
    int rw = 0;
    if (infilename){
        if (strcmp(infilename, outfilename)){
            rw = 1;
            infile = fopen(infilename, "r+");
            outfile = infile;
        } else {
            infile = fopen(infilename, "r");
        }
    }
    if (outfilename && rw){
        outfile = fopen(outfilename, "w");
    }
    
    struct universe v;
    
    int (*function)(struct universe *, int, int) = will_be_alive;
    if (torus){
        function = &will_be_alive_torus;
    }

    read_in_file(infile,&v);

    for (int i = 0; i < generations; i++){
        evolve(&v,function);
    }
    write_out_file(outfile,&v);
    if (printStats){
        printf("Printing stats!");
    }
    return 0;
}
