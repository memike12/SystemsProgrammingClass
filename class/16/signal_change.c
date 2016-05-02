#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


void goodbye(){
  printf("Goodbye World!\n");
  signal(SIGUSR1, SIG_DFL);
}

void hello(){
  printf("Hello World!\n");
  signal(SIGUSR1, goodbye);
}

int main(){

  pid_t cpid;

  if ( (cpid = fork()) == 0){
    /*CHILD*/

    kill(getppid(), SIGUSR1);
    sleep(1);
    kill(getppid(), SIGUSR1);
    sleep(1);
    kill(getppid(), SIGUSR1);
    exit(0);
  }else{
    /*PARENT*/

    signal(SIGUSR1, hello);

    wait(NULL);
  }

}
