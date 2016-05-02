#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>


int main(){

  int prio;

  prio = getpriority(PRIO_PROCESS, 0); //get the priority of this process
  printf("Priority: %d\n",prio);


  //setting negative priority requires priveledged mode
  if( nice(-5) != -5){ //checking errors with nice is different
    perror("nice");    //return values can be NEGATIVE
    return 1;
  }
    

  prio = getpriority(PRIO_PROCESS, 0); //get the priority of this process
  printf("Priority: %d\n",prio);


  return 0;

}
