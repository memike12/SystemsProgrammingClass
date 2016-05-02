#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <sys/signal.h>

int main(){

  //ignore SIGSTOP ?
  if( signal(SIGKILL, SIG_IGN) == SIG_ERR){
    perror("signal");;
    exit(1);
  }
  
  //infinite loop
  while(1);

}
