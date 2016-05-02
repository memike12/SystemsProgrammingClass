#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

  if(argc<2){
    fprintf(stderr, "Usage: '%s n', creates 2^n processes \n", argv[0]);
    exit(1);
  }

  //fork count times, read from command line
  int count = atoi(argv[1]);
  while(count){
    fork();
    count--;
  }

  //loop forever
  while(1);
}
