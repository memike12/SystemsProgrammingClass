#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mathlib.h"

#include <readline/readline.h>

#define STACK_SIZE 128

int main(){
  
  char * line, * tok;
  int x,i;

  int shead=0;
  int stack[STACK_SIZE];
  
  int error=0;

  while(1){
    error=0;
    shead=0;
    line = readline("(Ctrl-D to EXIT))\nRPN> ");

    if(line == NULL){
      printf("\n");
      free(line);
      break;
    }

    tok = strtok(line, " ");
    do{
      
      //check number
      if(sscanf(tok, "%d", &x) == 0){
	//not a number

	if(strlen(tok) > 1){ //not a 1 char symbol, error

	  fprintf(stderr, "ERROR: Unkown symbol '%s'\n", tok);
	  error=1;
	  break;
	}else if(tok[0] == '+'){ //plus
	  if(shead >= 2){
	    stack[shead-2] = add(stack[shead-2], stack[shead-1]);
	    shead--;
	  }else{
	    fprintf(stderr, "ERROR: Not enough arguments\n");
	    error=1;
	    break;
	  }      
	  
	}else if(tok[0] == '-'){ //minus
	  if(shead >= 2){
	    stack[shead-2] = minus(stack[shead-2], stack[shead-1]);
	    shead--;
	  }else{
	    fprintf(stderr, "ERROR: Not enough arguments\n");
	    error=1;
	    break;
	  }
	}else if(tok[0] == '*'){ //mult
	  if(shead >= 2){
	    stack[shead-2] = mult(stack[shead-2], stack[shead-1]);
	    shead--;
	  }else{
	    fprintf(stderr, "ERROR: Not enough arguments\n");
	    error=1;
	    break;
	  }
	}else if(tok[0] == '/'){ //divide
	  if(shead >= 2){
	    stack[shead-2] = divide(stack[shead-2], stack[shead-1]);
	    shead--;
	  }else{
	    fprintf(stderr, "ERROR: Not enough arguments\n");
	    error=1;
	    break;
	  }
	}else if(tok[0] == '!'){ //factorial
	  if(shead >= 1){
	    stack[shead-1] = fact(stack[shead-1]);
	  }else{
	    fprintf(stderr, "ERROR: Not enough arguments\n");
	    error=1;
	    break;
	  }
	}else{ //not a symbol we know
	  fprintf(stderr, "ERROR: Unkown symbol '%s'\n", tok);
	  error=1;
	  break;
	}
      }else{ //add a number to stack
	if(shead < STACK_SIZE){
	  stack[shead] = x;
	  shead++;
	  }else{
	  error=1;
	  fprintf(stderr, "ERROR: Stack full\n");
	  break;
	}
      }
      
    }while( (tok = strtok(NULL, " "))  != NULL); //continue parse
    
    //print result
    if(! error){
      for(i=shead-1;i>=0;i--){
	printf("%d: %d\n", i, stack[i]);
      }
    }
    
    
    free(line);
  }//continue loop
  


  return 0;
}
