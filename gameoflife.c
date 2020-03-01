#include<stdio.h>
#include<stdlib.h>
#include"gol.h"
int main(int argc, char *argv[]){
  struct universe v; 
  read_in_file(stdin,&v);
  for (int i = 0; i < (int)atoi(argv[1]); i++){
      evolve(&v,will_be_alive);
  }
  printf("%i", argc);
  /*
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);*/
  write_out_file(stdout,&v);
return 0;
}
