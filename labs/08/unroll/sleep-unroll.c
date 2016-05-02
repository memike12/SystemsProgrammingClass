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

/************************************************************
 * sleep-unroll.c
 *
 * Unroll a pipeline of sleep calls, placing all children in their own
 * process group. 
 *
 * Sample Usage:
 *  $ ./sleep_unroll "sleep 1"   
 *  $ ./sleep_unroll "sleep 1 | sleep 2"
 *  $ ./sleep_unrill "sleep 2 | sleep 3 | sleep 1"
 *
 ************************************************************/


int main(int argc, char * argv[]){

  pid_t cpid;
  pid_t cpgid=0; 

  int i, status;
  char * cmd_argv[MAX_ARGS];
  char * line, * tok;
   
  //split the command based on | into lines
  line = strtok(argv[1], "|");
  do{
    cpid = fork();
    if (cpgid == 0){
      cpgid = cpid;
    }
     if( cpid ==  0){

       tok = strtok(line, " ");
       i = 0;
       cmd_argv[i] = tok;
       while (( tok = strtok(NULL, " ")) != NULL && i < MAX_ARGS){
         i++;
         cmd_argv[i] = tok;
       }
       i++;
       cmd_argv[i] = NULL;

       execvp(cmd_argv[0], cmd_argv);
       perror("wait");
       exit(2);
     }
 
     else if(cpid > 0){
       setpgid(cpid, cpgid);
     }
     
  }while( (line = strtok(NULL, "|")) != NULL);

  //wait for all children in a process group
  while(waitpid(-cpgid, &status, 0) > 0); //DO NOT EDIT
	 
  //SUCCESS!
  return 0;
}
