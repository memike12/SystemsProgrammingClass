#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>


void * hello_arg(void * args){

  char * str = (char *) args;
  
  printf("%s", str);

  return NULL;
}

int main(int argc, char * argv[]){

  char hello[] = "Hello World!\n";

  pthread_t thread;  //thread identifier
  
  //create a new thread that runs hello_arg with argument hello
  pthread_create(&thread, NULL, hello_arg, hello);
  
  //wait until the thread completes
  pthread_join(thread, NULL);

  return 0;
}
