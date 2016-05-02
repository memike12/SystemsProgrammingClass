#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>

char USAGE[] = "naive_lock n_threads\n"
  "USAGE: run n threads with a naive lock\n";

int lock = 0;

int shared = 0;

void * incrementer(void * args){
  int i;

  for(i=0;i<100;i++){

    //check lock
    while(lock > 0);  //spin until unlocked
      
    lock = 1; //set lock
    
    shared++; //increment
      
    lock = 0; //unlock
  }
  
  return NULL;
}


int main(int argc, char * argv[]){
  pthread_t * threads;
  int n,i;

  if(argc < 2){
    fprintf(stderr, "ERROR: Invalid number of threads\n");
    exit(1);
  }

  //convert argv[1] to a long
  if((n = atol(argv[1])) == 0){
    fprintf(stderr, "ERROR: Invalid number of threads\n");
    exit(1);
  }

  //allocate array of pthread_t identifiers
  threads = calloc(n,sizeof(pthread_t));

  //create n threads
  for(i=0;i<n;i++){
    pthread_create(&threads[i], NULL, incrementer, NULL);
  }

  //join all threads
  for(i=0;i<n;i++){
    pthread_join(threads[i], NULL);
  }

  //print shared value and result
  printf("Shared: %d\n",shared);
  printf("Expect: %d\n",n*100);
  
  return 0;
}

  
