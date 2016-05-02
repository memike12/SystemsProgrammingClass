#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
  
  pid_t c_pid,pgid,pid;

  c_pid = fork();

  if(c_pid == 0){
    /* CHILD */
    
    pgid = getpgrp();
    pid = getpid();

    printf("Child:  pid: %d pgid: *%d*\n", pid, pgid);

    
  }else if (c_pid > 0){
    /* PARRENT */
    
    pgid = getpgrp();
    pid = getpid();


    printf("Parent: pid: %d pgid: *%d*\n", pid, pgid);
    

  }else{
    /* ERROR */
    perror(argv[0]);
    _exit(1);
  }

  return 0;
}
