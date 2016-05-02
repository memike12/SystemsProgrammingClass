#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  int i;
  for(i=0; i<10;i++){

    if(fork() == 0){ //create a child
      _exit(0); // and exit
    }

  }

  while(1); //run forever
}
