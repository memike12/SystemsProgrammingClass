#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){

  int status;
  int pfd[2];
  pid_t cpid;
  char c;

  //open a pipe, pfd[0] for reading, pfd[1] for writing
  if ( pipe(pfd) < 0){
    perror("pipe");
    return 1;
  }

  //Setup a pipe between child 1 and child 2, like:
  // parent | child
  
  cpid = fork();
  
  if( cpid == 0 ){
    /* CHILD 1*/
    
    //close stdin
    close(0);
    
    //duplicate reading end to stdin
    dup2(pfd[0], 0);

    //close the writing end
    close(pfd[1]);

    //try and read 1 byte from stding and write stdout
    while( read(0, &c, 1) > 0){ //stdin now pipe!
      write(1, &c,1); //this is still stdout
    }

    exit(0);
  } else if ( cpid > 0){
    /* PARENT */
    
    //close stdout
    close(1);
    
    //duplicate writing end to stdout
    dup2(pfd[1], 1);
    
    //close reading end 
    close(pfd[0]);


    //read and read 1 byte from stdin, write byte to pipe
    while( read(0,&c,1) > 0){
      write(1, &c, 1);
    }

    //close the pipe and stdout
    close(pfd[1]);
    close(1);

    //wait for child
    wait(&status);
    
  }else{
    /* ERROR */
    perror("fork");
    return 1;
  }

  return 0;
}
