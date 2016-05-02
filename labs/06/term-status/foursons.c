#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> //for fork() 
#include <sys/types.h> //for pid_t, sleep()
#include <sys/wait.h> //for wait(), and macros

#include <string.h> //for strsignal()

int main(){

  pid_t c_pid[4]; //array of 4 children pid's
  pid_t pid;
  int i, status;

  for(i = 0; i < 4; i ++){

    c_pid[i] = fork();

    if (c_pid[i] == 0){
      /* Child */
      pid = getpid();

      switch(i){
      case 0:
	//Child 0: The wise son
	printf("Child 0: %d: Sleeping 1 second, Exiting status 16\n", pid);
	
	sleep(1); //sleep 1 sec
	exit(16); //exit 
	break;
      case 1:
	//Child 1: The simple son
	printf("Child 1: %d: I'm going to dereference a NULL pointer\n", pid);
	
	int * p = NULL; 
	*p = 10; //dereferencing NULL
	  
	exit(1);//just in case
	break;
      case 2:
	//Child 2: The wicked son
	printf("Child 2: %d: I'm going to shoot myself with a SIGABRT because I can\n", pid);
	
	kill(pid, SIGABRT);
	exit(1);//just in case
	break;
      case 3:
	//Child 3: The son who doesn't know how to ask question
	printf("Child 3: %d: Ummm ....\n", pid);
	exit(0); //success?
	break;
      }
      
    }
  }

  /*Parent*/
  
  //TODO: Wait on all children and print some status.
  int k;
  for (int i = 3; i>=0; i--)
  {
    pid = wait(&status);
    for (int j=0;j<4;j++){
      if(c_pid[j]==pid){
        k = j;
      }
    }
    //for(int j = 0; j<4; j++){
    if ( WIFEXITED(status) ){
      printf("Parent: Child %d: %d terminated and exited with status %d\n", k, pid, WEXITSTATUS(status));
      }
    else if(WIFSIGNALED(status)){
      printf("Parent: Child %d: %d terminated and exited due to signal %s and also core dumped \n", k, pid, strsignal( WTERMSIG(status) ));
      }

  }
  
   
  
  return 0;
}
