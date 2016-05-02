#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>

void alarm_handler(int signum){
  printf("Buzz Buzz Buzz\n");

  //set a new alarm for 1 second
  alarm(1);
}

int main(){

  //set up alarm handler
  signal(SIGALRM, alarm_handler);

  //schedule the first alarm
  alarm(1);

  //pause in a loop
  while(1){
    pause();
  }

}
