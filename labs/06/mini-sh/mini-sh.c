#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

#define MAX_ARGS 128

int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y) {
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }
     
  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;
     
  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}


int main(int argc, char * argv[]){


  char * line;    //DO NOT EDIT, for readline
  char prompt[256];    //DO NOT EDIT, for readline



  pid_t c_pid; //NOTE: to store child pid
  int status, i; //NOTE: For wait status and iteration
  
  char * cmd_argv[MAX_ARGS]; //NOTE: use this store your argv array, 
                             //      don't go beyond MAX_ARGS

  char * tok;   //NOTE: This is useful for tokenizatoin

  struct timeval start, end, diff; //for timing

  start.tv_sec = 0;
  start.tv_usec = 0;
  diff = end = start; //initialize times to zero
  
  //for readline setup, don't edit!
  rl_bind_key('\t', rl_abort);

  while(1){
    

    //prompt
    snprintf(prompt, 256, "mini-sh (%ld.%04ld) #> ", diff.tv_sec, diff.tv_usec/1000);

    //readline allocates a new line every time it reads
    line = readline(prompt); 
    
    //read EOF, break the loop
    if (line == NULL){
      free(line);
      printf("\n");
      break;
    }

    //read empty line, continue
    if (strcmp(line,"")==0){
      free(line);
      continue;
    }

    //TODO: Tokenize the line to construct a argv array
    //retrieve first token from line, seperated using " " 
    tok = strtok(line, " ");
    i = 0;
    cmd_argv[i] = tok;
    //continue to retrieve tokens until NULL returned
    while( (tok = strtok(NULL, " ")) != NULL){
       i++;
       cmd_argv[i] = tok;
    }
    i++;
    cmd_argv[i] = NULL;
    //TODO: Fork-Exec-Wait the command, and compute the time of execution
    //      store the time of execution in diff so that it will be 
    //      available in the next prompt.
    

    //HINT: Make sure you *always& exit in the child, in case exec
    //      fails. This could cause a fork bomb
    
    gettimeofday(&start, 0);
    c_pid = fork();
    if (c_pid == 0){
      /* CHILD */
      //execute ls            
       execvp( cmd_argv[0], cmd_argv);
      //only get here if exec failed                                                                                                                                        
      perror("execve failed");
      _exit(0);
    }else if (c_pid > 0){
      /* PARENT */

      if( (c_pid = wait(&status)) < 0){
        perror("wait");
        _exit(1);
      }
      gettimeofday(&end, 0);

    }else{
      perror("fork failed");
      _exit(1);
    }

    timeval_subtract(&diff, &end, &start);
    //printf("Run Time: %ld.%04ld (s)\n", diff.tv_sec, diff.tv_usec/1000);


    free(line); //free the current line, otherwise memleak
  }

  return 0;
}
