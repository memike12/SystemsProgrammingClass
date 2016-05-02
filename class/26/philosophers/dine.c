#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>

#include <pthread.h>

//HINT: Why not change these to something smaller to do testing?
#define NUM_PHIL 10
#define ROUNDS 1000

struct fork{
  int id;
  pthread_mutex_t * lock; //the lock on the fork
};


struct philosopher{
  int id;               //id of this philosopher
  struct fork * left;   //the left fork
  struct fork * right;  //the right fork
  pthread_t thread_id; //POSIX thread id
};

struct fork forks[NUM_PHIL];
struct philosopher philosophers[NUM_PHIL];

void  * eat(void * args){
  struct philosopher * phil  = (struct philosopher *) args;
  int i;

  for (i = 0;i<ROUNDS;i++){
    //TODO: fix locking to avoid deadlock 

    printf("Philosopher %d ACQUIRING left fork %d\n", phil->id, phil->left->id);
    pthread_mutex_lock(phil->left->lock);

    printf("Philosopher %d ACQUIRING right fork %d\n", phil->id, phil->right->id);
    pthread_mutex_lock(phil->right->lock);

    printf("Philosopher %d EATING with fork %d and %d\n", phil->id, phil->left->id, phil->right->id);
    usleep(250); //sleep for a quarter second

    printf("Philosopher %d RELEASING fork %d\n", phil->id, phil->left->id);
    pthread_mutex_unlock(phil->left->lock);
    printf("Philosopher %d RELEASING fork %d\n", phil->id, phil->right->id);
    pthread_mutex_unlock(phil->right->lock);
  }

  return NULL;
}

int main(){
  
  int i;

  printf("Initializing forks: %d\n", NUM_PHIL-1);
  //initialize the forks
  for(i=0;i<NUM_PHIL;i++){
    forks[i].id = i;
    forks[i].lock = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(forks[i].lock, NULL);
  }
  
  printf("Initializing philosophers: %d\n", NUM_PHIL);
  //initialize the philosophers
  for(i=0;i<NUM_PHIL;i++){
    philosophers[i].id = i;
    if( i == 0){
      philosophers[i].left = &forks[(NUM_PHIL-1)];
    }else{
      philosophers[i].left = &forks[i-1];
    }

    philosophers[i].right = &forks[(i) % NUM_PHIL];
  }

  
  printf("Starting Threads\n");
  //start the threads
  for(i=0;i<NUM_PHIL;i++){
    pthread_create(&(philosophers[i].thread_id), NULL,
		   eat, (void *) &(philosophers[i]));
  }
  
  //join the threads
  for(i=0;i<NUM_PHIL;i++){
    pthread_join(philosophers[i].thread_id, NULL);
  }

  printf("All threads joined\n");
  //clean memory
  for(i=0;i<NUM_PHIL-1;i++){
    pthread_mutex_destroy(forks[i].lock);
    free(forks[i].lock);
  }
  
  return 0;
}
