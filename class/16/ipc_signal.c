#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void hello(){
  printf("Hello World!\n");
}

int main(){

  pid_t cpid;
  pid_t ppid;

  //set handler for SIGUSR1 to hello()
  signal(SIGUSR1, hello);

  if ( (cpid = fork()) == 0){
    /*CHILD*/
    
    //get parent's pid
    ppid = getppid();

    //send SIGUSR1 signal to parrent
    kill(ppid, SIGUSR1);
    exit(0);
  }else{
    /*PARENT*/
    
    //just wait for child to terminate
    wait(NULL);
  }

}
