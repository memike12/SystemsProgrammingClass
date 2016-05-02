#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_ARGS 128

//global last_pid: -1 no background job, > 0 pid of background job
pid_t last_pid = -1;

////////////////////////////////////////////////////
//*DO* EDIT BELOW

void my_wait(){
  pid_t pid;
  int status;

  //wait for child to change state 
  while(1){

    if ( (pid = waitpid(-1, &status, WUNTRACED)) < 0){
      perror("wait failed");
      _exit(2);
    }

    //TODO: Check if process changed state due to being stopped
    //      if so, and no background process, save pid and break loop
    //      if background process already, continue that process, and continue waiting
    //      if process changed state for another reason, termination, break loop

    if(WIFSTOPPED(status)){
      last_pid = pid;
    }


    break; //break loop on child state change, but will want to adjust
	   //logic in your solution
  }

  if(tcsetpgrp(0,getpid()) < 0){
    perror("tcsetpgrp");
  }
  //Dont' forget to reclaim terminal control for the the shell!
  return;
}

////////////////////////////////////////////////////
//DO NOT EDIT BELOW

int main(int argc, char * argv[]){


  char * line; 
  pid_t c_pid;
  int i;
  char * cmd_argv[MAX_ARGS]; //NOTE: use this store your argv array, 
                             //      don't go beyond MAX_ARGS
  char prompt[1024];
  char * tok;   //NOTE: This is useful for tokenizatoin

  //Need to ignore these signals for terminal control to work
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);

  
  //for readline setup, don't edit!
  rl_bind_key('\t', rl_abort);



  while(1){ //fork/exec/wait loop

    //setup the prompt
    snprintf(prompt, 1024, "fg-shell (%d) #> ",last_pid);
    line = readline(prompt);   //readline allocates a new line every time, need to free
    
    //read EOF, break
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


    ////////////////////////////////////////////////////////////////
    //*DO* EDIT BELOW
    //
    
    //FILL IN COMPLETED SOLUTION FROM LAB 5
    //  - parsing line using strtok into the cmd_argv array

    //TODO: See if user entered "fg" command 
    //      If so, try and start the background process and call my_wait()
    //      If no last background process, report error to STDERR
    //      Don't forget to give the foreground process control of the terminal

    //perform a foreground
    if ( strcmp(cmd_argv[0], "fg") == 0){


      //TODO: FILL IN HERE


      free(line); //free line
      continue; //continue the shell after waiting
    }


    //////////////////////////////////////////////////////////////
    //DO NOT EDIT BELOW
    //

    if ( (c_pid = fork()) == 0 ){
      /* CHILD */

      //set as it's own process group
      setpgrp();
      
      execvp(cmd_argv[0],cmd_argv);
      perror("fg-shell"); //error
      _exit(2); //hard exit, don't want a fork bomb!

    }else if (c_pid > 0){
      /* PARENT */

      //give child its own process group
      if(setpgid(c_pid, c_pid) < 0){
	perror("setpgrp");
      }

      //give child the terminal control
      if( tcsetpgrp(0, c_pid) < 0){
	perror("tcsetpgrp");
      }

      //wait for a state change
      my_wait();
      
    }else{
      /* ERROR */
      perror("fork failed");
      _exit(2);
      
    }
    
    free(line); //free the current line
  } 
  return 0;
}

