#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>


void * hello_fun(void * args){

  while(1){
    //busy wait
  }

  return NULL;
}

int main(int argc, char * argv[]){

  pthread_t thread[4];  //thread identifier
  int i;

  //create 4 threads
  for(i = 0 ; i < 4; i++){
    pthread_create(&thread[i], NULL, hello_fun, NULL);
  }

  //wait for all threads to finish
  for(i = 0 ; i < 4; i++){
    pthread_join(thread[i], NULL);
  }

  return 0;
}
