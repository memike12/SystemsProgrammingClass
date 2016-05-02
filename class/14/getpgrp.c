#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
  
  pid_t pid, pgid; //process id and process group for this program
  pid_t ppid, ppgid; //process id and proces group for the _parent_
 
  //current
  pid = getpid();
  pgid = getpgrp();

  //parent
  ppid = getppid();
  ppgid = getpgid(ppid);

  //print this parent's process pid and pgid
  printf("%s: (current) pid:%d pgid:%d\n", argv[0], pid, pgid);
  printf("%s: (parrent) ppid:%d pgid:%d\n", argv[0], ppid, ppgid);

  return 0;
}
