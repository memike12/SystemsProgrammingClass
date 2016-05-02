#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>

void sigint_handler(int signum){
  printf("Snoozing!\n");

  //schedule next alarm for 5 seconds
  alarm(5);
}

void alarm_handler(int signum){
  printf("Buzz Buzz Buzz\n");

  //set a new alarm for 1 second
  alarm(1);
}

int main(){

  //set up alarm handler
  signal(SIGALRM, alarm_handler);

  //set up signint handler
  signal(SIGINT, sigint_handler);

  //schedule the first alarm
  alarm(1);

  //pause in a loop
  while(1){
    pause();
  }

}
