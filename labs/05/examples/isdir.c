#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){

  struct stat st;

  if( argc < 2){
    fprintf(stderr, "ERROR: Require a path\n");
    return 2;   //return status error
  }


  if( stat(argv[1], &st) < 0){     //error, cannot stat file
    perror(argv[0]);               //report erro with perror
    return 2;                     //return status error
  }

  if ( S_ISDIR(st.st_mode) ){
    printf("It's a directory!\n");
    return 0;  //return status true
  }

  printf("Not a directory :(\n");
  return 1; //return status false

}  
