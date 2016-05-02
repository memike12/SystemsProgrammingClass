#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char * argv[]){

  int i;
  char * line; 
  char * tok;

  //for readline setup, don't edit!
  rl_bind_key('\t', rl_abort);

  while(1){
    
    //readline allocates a new line every time it reads
    line = readline("token-sh > "); 
    
    //read EOF
    if (line == NULL){
      free(line);
      printf("\n");
      break;
    }

    //read empty line
    if (strcmp(line,"")==0){
      free(line);
      continue;
    }


    //retrieve first token from line, seperated using " "
    tok = strtok(line, " "); 
    
    i = 0;
    printf("%d: %s\n", i, tok);
    
    //continue to retrieve tokens until NULL returned
    while( (tok = strtok(NULL, " ")) != NULL){
      i++;
      printf("%d: %s\n", i, tok);
    }

    free(line); //free the current line from readline
  }

  return 0;
}
