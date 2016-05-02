#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){

  char c = 'A';
  int i;
  int pfd[2]; //pfd[0] reading end of pipe
              //pdf[1] writing end of pipe
  
  //open the pipe
  if( pipe(pfd) < 0){
    perror("pipe");
    return 1;
  }

  //set pipe to not block
  fcntl(pfd[1], F_SETFL, O_NONBLOCK);
  
  //write A's to pipe until it's full
  i = 0;
  while( write(pfd[1], &c, 1) > 0){
    printf("%d\n",i);
    i++;
  }
  perror("write");

  //close write end of pipe
  close(pfd[1]);

  //read from pipe?!?
  while( read(pfd[0], &c, 1)){
    write(1, &c, 1);
  }

  close(pfd[0]);

  return 0;
}
  
