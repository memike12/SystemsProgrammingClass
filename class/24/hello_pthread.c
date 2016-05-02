#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
int a =0;

void * hello_fun(void * args){

  printf("Hello World!\n");
  a = 2;
  return NULL;
}

int main(int argc, char * argv[]){

  pthread_t thread;  //thread identifier
  
  //create a new thread have it run the function hello_fun
  pthread_create(&thread, NULL, hello_fun, NULL);
  
  //wait until the thread completes
  pthread_join(thread, NULL);
  printf("%d\n", a);
  return 0;
}
