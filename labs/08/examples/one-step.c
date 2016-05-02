#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

  // cat sample-db | grep MD
  char * cmd1[] = {"cat", "sample-db.csv", NULL};
  char * cmd2[] = {"grep", "MD", NULL};

  int pipe_fd[2];
  int status;

  pid_t cpid1,cpid2;

  //open the pipe in parent
  if(pipe(pipe_fd) < 0){
    perror("pipe");
    _exit(1);
  }
  
  cpid1 = fork();
  if( cpid1 ==  0){
    /* CHILD 1*/

    //redirect output to the pipe
    close(pipe_fd[0]); //close read end of pipe    
    close(1);//close stdout
    dup2(pipe_fd[1], 1); //duplicate pipe to stdout
    
    //execute the comand
    execvp(cmd1[0], cmd1);
    perror("exec");
    _exit(1);
  }else if(cpid1 < 0){
    /* ERROR */
    perror("fork");
    _exit(1);
  }

  cpid2 = fork();
  if(cpid2 == 0){
    /* CHILD 2*/


    //redirect input from the pipe
    close(pipe_fd[1]); //close write end of pipe
    close(0); //close stdin
    dup2(pipe_fd[0],0); //duplicate pipe to stdin

    //execute the comand
    execvp(cmd2[0], cmd2);
    perror("exec");
    _exit(1);
  }else if(cpid2 < 0){
    /* ERROR */
    perror("fork");
    _exit(1);
  }

  /* PARENT */

  //widow pipe by closing write end of pipe
  close(pipe_fd[1]);

  //wait on all children
  while(wait(&status) > 0 );

  //sucess
  return 0;
}



