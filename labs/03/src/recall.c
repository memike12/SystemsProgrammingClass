#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]){
  
  int c;
  FILE * input;
  
  //TODO: Complte the program
  if((input = fopen("saved.out", "r")) == NULL){
    fprintf(stderr,"ERROR: Cannot open output file for reading\n");
    exit(1); 
  }

  while((c = fgetc(input)) != EOF){
    printf("%c", c);
  }
  fclose(input);


  return 0;
}
