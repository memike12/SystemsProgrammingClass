#include <stdlib.h>
#include <stdio.h>

#include <signal.h>

void hello(int signum){
  printf("Hello World!\n");
}

int main(){
  
  //execute hell() when receiving signal SIGUSR1
  signal(SIGUSR1, hello);

  //send SIGUSR1 to the calling process
  raise(SIGUSR1);

}
