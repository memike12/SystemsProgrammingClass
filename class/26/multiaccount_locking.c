#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pthread.h>

#define INIT_BALANCE 1000
#define NUM_TRANS 100
#define MAX_TRANS 10
#define NUM_ACCOUNTS 10

//create an account
struct account{
  int balance;
  int credits;
  int debits;
  pthread_mutex_t lock;
};

//array of accounts
struct account accounts[NUM_ACCOUNTS];


void * transactions(void * args){
  int i,v;
  int a1,a2;

  for(i=0;i<NUM_TRANS;i++){

    //choose a random value
    v = (int) random() % NUM_TRANS;

    //choose two random accounts
    a1 = (int) random() % NUM_ACCOUNTS;
    while((a2 = (int) random() % NUM_ACCOUNTS) == a1);

    //transfer from a1 to a2

    if(a1 < a2){
      pthread_mutex_lock(&accounts[a1].lock);
      pthread_mutex_lock(&accounts[a2].lock);
    }else{
      pthread_mutex_lock(&accounts[a2].lock);
      pthread_mutex_lock(&accounts[a1].lock);
    }

    accounts[a1].balance += v;
    accounts[a1].credits  += v;

    accounts[a2].balance -= v;
    accounts[a2].debits += v;

    if(a1 < a2){
      pthread_mutex_unlock(&accounts[a2].lock);
      pthread_mutex_unlock(&accounts[a1].lock);
    }else{
      pthread_mutex_unlock(&accounts[a1].lock);
      pthread_mutex_unlock(&accounts[a2].lock);
    }
  }

  return 0;
}


int main(int argc, char * argv[]){

  int n_threads,i;
  pthread_t * threads;

  //error check
  if(argc < 2){
    fprintf(stderr, "ERROR: Require number of threads\n");
    exit(1);
  }
  
  //convert string to int
  n_threads = atol(argv[1]);

  //error check
  if(n_threads <= 0){
    fprintf(stderr, "ERROR: Invalivd value for number of threads\n");
    exit(1);
  }

  //allocate array of thread identifiers
  threads = calloc(n_threads, sizeof(pthread_t));

  //initialize accounts
  for(i=0;i<NUM_ACCOUNTS;i++){
    accounts[i].balance=INIT_BALANCE;
    accounts[i].credits=0;
    accounts[i].debits=0;
    pthread_mutex_init(&accounts[i].lock, NULL);
  }

  //start all threads
  for(i=0;i<n_threads;i++){
    pthread_create(&threads[i], NULL, transactions, NULL);
  }

  //join all threads
  for(i=0;i<n_threads;i++){
    pthread_join(threads[i], NULL);
  }

  for(i=0;i<NUM_ACCOUNTS;i++){
    printf("ACCOUNT %d: %d (%d)\n", i, accounts[i].balance, 
	   INIT_BALANCE+accounts[i].credits-accounts[i].debits);
  }

  //free array
  free(threads);
  
  //destroy locks
  for(i=0;i<NUM_ACCOUNTS;i++){
    pthread_mutex_destroy(&accounts[i].lock);
  }
}
