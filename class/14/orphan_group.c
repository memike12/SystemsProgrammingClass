#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
  
  pid_t cpid;

  cpid = fork();

  if( cpid == 0 ){
    /* CHILD */

    //set process group to itself
    setpgrp();

    //child loops forever!
    while(1);

  }else if( cpid > 0 ){
    /* PARRENT */
    
    //set the proccess group of child 
    setpgid(cpid, cpid); 

    //Parrent loops forever
    while(1);

  }else{
    /*ERROR*/
    perror("fork");
    _exit(1);
  }
    

  return 0;
}
