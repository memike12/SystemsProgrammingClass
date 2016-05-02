#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

  pid_t c_pid;


  c_pid = fork(); //duplicate

  
  if( c_pid == 0 ){
    //child: The return of fork() is zero

    printf("Child: I'm the child: %d\n", c_pid);

  }else if (c_pid > 0){
    //parent: The return of fork() is the process of id of the child

    printf("Parent: I'm the parent: %d\n", c_pid);
 
  }else{
    //error: The return of fork() is negative

    perror("fork failed");
    _exit(2); //exit failure, hard

  }

  return 0; //success
}
