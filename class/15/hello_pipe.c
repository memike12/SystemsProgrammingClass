#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){

  //print hello world through a pipe!
  char hello[] = "Hello World!\n";
  char c;

  int pfd[2]; //pfd[0] reading end of pipe
              //pfd[1] writing end of pipe
  

  //open the pipe
  if( pipe(pfd) < 0){
    perror("pipe");
    return 1;
  }
  
  //write hello world to pipe
  write(pfd[1], hello, strlen(hello));
  
  //close write end of pipe
  close(pfd[1]);

  //read hello world from pipe, write to stdout
  while( read(pfd[0], &c, 1)){
    write(1, &c, 1);
  }

  close(pfd[0]);

  return 0;
}
  
