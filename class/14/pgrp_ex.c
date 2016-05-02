#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
  
  pid_t c_pid,pid;
  int status;
  char error_msg[1024];
    
  if (argc < 2){
    fprintf(stderr, "%s: Require argument\n", argv[0]);
    _exit(1);
  }

  c_pid = fork();

  if(c_pid == 0){
    /* CHILD */

    printf("Child: pid:%d pgid:%d\n", getpid(), getpgrp());

    //set the process group to itself  <<-- duplicated in parent
    setpgrp();

    printf("Child: pid:%d pgid:%d\n", getpid(), getpgrp());

    execvp(argv[1], argv+1);
    snprintf(error_msg, 1024, "%s: %s:", argv[0], argv[1]);
    perror(error_msg);
    
  }else if (c_pid > 0){
    /* PARRENT */


    printf("Parent: pid:%d pgid:%d\n", getpid(), getpgrp());
    printf("Parent: Child's: pid:%d pgid:%d\n", c_pid, getpgid(c_pid));

    //set the process group of child to itself <<-- duplicated in child
    setpgid(c_pid, c_pid);

    if( (pid = wait(&status)) < 0){
      perror(argv[0]);
      _exit(1);
    }


  }else{
    /* ERROR */
    perror(argv[0]);
    _exit(1);
  }




}
