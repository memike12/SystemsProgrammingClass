#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){

  int status;
  pid_t cpid, pid;

  int i=0;
  
  while(1){ //loop and fork children

    cpid = fork();
    
    if( cpid == 0 ){
      /* CHILD */
      
      pid = getpid();
      
      printf("Child: %d: i:%d\n", pid, i);

      //set i in child to somethign differnt
      i *= 3;
      printf("Child: %d: i:%d\n", pid, i);
 
      _exit(0); //NO FORK BOMB!!!
    }else if ( cpid > 0){
      /* PARENT */
      
      //wait for child
      wait(&status);

      //print i after waiting
      printf("Parent: i:%d\n", i);

      i++;
      if (i > 5){	
	break; //break loop after 5 iterations
      }

    }else{
      /* ERROR */
      perror("fork");
      return 1;
    }
    
    //pretty print
    printf("--------------------\n");
  }

  return 0;
}
