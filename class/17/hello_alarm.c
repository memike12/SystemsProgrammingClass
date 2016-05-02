#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>

void alarm_handler(int signum){
  printf("Buzz Buzz Buzz\n");
}

int main(){

  //set up alarm handler
  signal(SIGALRM, alarm_handler);

  //schedule alarm for 1 second
  alarm(1);

  //do not proceed until signal is handled
  pause();

}
