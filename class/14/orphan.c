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

    //child loops forever!
    while(1);

  }else if( cpid > 0 ){
    /* PARRENT */
    
    //Parrent loops forever
    while(1);

  }else{
    /*ERROR*/
    perror("fork");
    _exit(1);
  }
    

  return 0;
}
