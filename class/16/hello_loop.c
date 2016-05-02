#include <stdio.h>
#include <stdlib.h>

#include <signal.h>

void hello(int signum){
  printf("Hello World!\n");
}

int main(){

  //Handle SIGINT with hello
  signal(SIGINT, hello);

  //loop forever!
  while(1);

}
