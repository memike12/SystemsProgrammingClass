#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]){
  
  int c;
  FILE * from, * to;

  //TODO: Complete the program
  if((from = fopen(argv[1], "r")) == NULL){
    fprintf(stderr,"ERROR: Cannot open input file for reading\n");
    exit(1); 
  }

  if((to = fopen(argv[2], "r")) == NULL){
    fprintf(stderr,"ERROR: Cannot open output file for writing\n");
    exit(1); 
  }

  while((c=fgetc(from)) != EOF){
    fputc(c, to);
  }
  fclose(to);
  fclose(from);
  return 0;
}
