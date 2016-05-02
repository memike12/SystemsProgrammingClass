#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]){
  
  int c;
  FILE * output;

  //TODO: Complete the program
  if((output = fopen("saved.out", "w")) == NULL){
    fprintf(stderr,"ERROR: fopen: file doesn't exist?\n");
    exit(1); 
  }

  while((c=fgetc(stdin)) != EOF){
    fputc(c, output);
  }
  fclose(output);
  return 0;
}
