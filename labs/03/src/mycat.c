#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
  
  int c,i;
  FILE * file;

  //TODO: Complete the program
  i = 1;
  if (argv[1] == NULL){
     while((c=fgetc(stdin)) != EOF){
       fprintf(stdout, "%c" , c);
     }
  }  
  while (argv[i] != NULL) {
     if (strcmp(argv[i], "-")==0){
       i++;
       //while(strcmp(argv[i], "<")!=0){
       //  i++;
         file = fopen(argv[i], "r");
         fprintf(stdin, "%c" , c);
         fclose(file);
         // }
     }
     if((file = fopen(argv[i], "r")) == NULL){
       fprintf(stderr,"ERROR: Cannot open file for reading\n"); 
       i++;
       //fclose(file);
       if ( i == argc){
       
       }
     }
     while((c=fgetc(file)) != EOF){
       fprintf(stdout, "%c" , c);
     }
    
     i++;
     fclose(file);
  }
}
