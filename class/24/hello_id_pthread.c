#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#include <pthread.h>

//have to call syscall directly, no libc wrapper
pid_t gettid(){
  return (pid_t) syscall (SYS_gettid);
}

void * hello_fun(void * args){

  //retrieve the thread_id
  pthread_t thread = pthread_self();

  //print all identifying information
  printf("THREAD: TID:%d PID:%d PthreadID:%lu\n", gettid(), getpid(), thread);

  return NULL;
}

int main(int argc, char * argv[]){

  pthread_t thread;  //thread identifier

  
  //create a new thread have it run the function hello_fun
  pthread_create(&thread, NULL, hello_fun, NULL);

  //print all identifying information
  printf("MAIN: TID:%d PID:%d \n", gettid(), getpid());

  //wait until the thread completes
  pthread_join(thread, NULL);

  return 0;
}
