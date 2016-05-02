#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){


  //print hello world through a pipe! To child!
  char hello[] = "Hello World!\n";
  char c;
  
  int pfd[2]; //pfd[0] reading end of pipe
              //pfd[1] writing end of pipe
  
  pid_t cpid;
  int status;

  //open a pipe, pfd[0] for reading, pfd[1] for writing
  if ( pipe(pfd) < 0){
    perror("pipe");
    return 1;
  }

  cpid = fork();
  
  if( cpid == 0 ){
    /* CHILD */
    
    //close the writing end in child
    close(pfd[1]);
    
    //try and read 1 byte from pipe, write byte stdout
    while( read(pfd[0], &c, 1) > 0){
      write(1, &c,1); 
    }
  
    //close pipe
    close(pfd[0]);
    
    _exit(0);    
  }else if ( cpid > 0){
    /* PARENT */

    //close reading end in parent
    close(pfd[0]);

    //write hello world to pipe
    write(pfd[1], hello, strlen(hello));

    //close the pipe
    close(pfd[1]);

    //wait for child
    wait(&status);
    
  }else{
    /* ERROR */
    perror("fork");
    return 1;
  }


  return 0;
}
