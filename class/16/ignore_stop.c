#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <sys/signal.h>

int main(){

  //ignore SIGSTOP ?
  signal(SIGSTOP, SIG_IGN);
  
  //infinite loop
  while(1);

}
