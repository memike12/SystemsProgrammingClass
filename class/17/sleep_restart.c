#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/types.h>

#include <string.h>

void handler(int signum){
  printf("Alarm\n");
  alarm(1);
}

int main(){

  struct sigaction action;
  action.sa_handler = handler;
  action.sa_flags = SA_RESTART; //<-- restart 

  sigaction(SIGALRM, &action, NULL);

  //alarm in 1 second
  alarm(1);

  //meanwhile sleep for 2 seconds
  sleep(2);

  //how long does the program run for?

}
