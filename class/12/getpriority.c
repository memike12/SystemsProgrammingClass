#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/resource.h>


int main(){

  int prio;
  
  prio = getpriority(PRIO_PROCESS, 0); //get the priority of this process

  printf("Priority: %d\n",prio);

  return 0;

}
