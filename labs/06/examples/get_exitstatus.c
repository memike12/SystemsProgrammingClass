#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(){

  pid_t c_pid, pid;
  int status;

  c_pid = fork(); //duplicate                                                                                                                                                


  if( c_pid == 0 ){
    //child
    pid = getpid();

    printf("Child: %d: I'm the child\n", pid);
    printf("Child: sleeping for 2-seconds, then exiting with status 12\n");

    //sleep for 2 seconds
    sleep(2);

    //exit with statys 12
    exit(12);

  }else if (c_pid > 0){
    //parent

    //waiting for child to terminate
    pid = wait(&status);

    if ( WIFEXITED(status) ){
      printf("Parent: Child exited with status: %d\n", WEXITSTATUS(status));
    }
    

  }else{
    //error: The return of fork() is negative                                                                                                                                

    perror("fork failed");
    _exit(2); //exit failure, hard                                                                                                                                           

  }

  return 0; //success                                                                                                                                                        
}



