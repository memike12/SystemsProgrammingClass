#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>

void handler(int signum){
  printf("Hello World!\n");
}

int main(){

  //declare a struct sigaction
  struct sigaction action;

  //set the handler
  action.sa_handler = handler;

  //call sigaction with the action structure
  sigaction(SIGALRM, &action, NULL);

  //schedule an alarm
  alarm(1);

  //pause
  pause();
}
