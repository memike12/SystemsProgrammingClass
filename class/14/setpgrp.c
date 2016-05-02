#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
  
  pid_t cpid, pid, pgid, cpgid; //process id's and process groups

  cpid = fork();

  if( cpid == 0 ){
    /* CHILD */

    //set process group to itself
    setpgrp();

    //print the pid, and pgid of child from child
    pid = getpid();
    pgid = getpgrp();
    printf("Child:          pid:%d pgid:*%d*\n", pid, pgid);

  }else if( cpid > 0 ){
    /* PARRENT */
    
    //print the pid, and pgid of parent
    pid = getpid();
    pgid = getpgrp();
    printf("Parent:         pid:%d pgid: %d \n", pid, pgid);    
 
    //print the pid, and pgid of child from parent
    cpgid = getpgid(cpid);
    printf("Parent: Child's pid:%d pgid:*%d*\n", cpid, cpgid);


  }else{
    /*ERROR*/
    perror("fork");
    _exit(1);
  }
    

  

  return 0;
}
