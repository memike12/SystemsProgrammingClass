#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>


int main(){

  int prio;

  prio = getpriority(PRIO_PROCESS, 0); //get the priority of this process
  printf("Priority: %d\n",prio);


  //any process can be nicer, but not greedier
  if( nice(10) != 10){
    perror("nice");
    return 1;
  }
    

  prio = getpriority(PRIO_PROCESS, 0); //get the priority of this process
  printf("Priority: %d\n",prio);


  return 0;

}
