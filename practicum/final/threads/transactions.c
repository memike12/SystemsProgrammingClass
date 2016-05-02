#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

//////////////////////////////////////////////////////////////////////
// DO NOT EDIT
#define NUM_TRANS 100000
#define NUM_THREADS 20
#define INIT_BALANCE 1000
/////////////////////////////////////////////////////////////////////


//NOTE: You must complete the exectue() and main() function

int balance = INIT_BALANCE; //shared balance

pthread_mutex_t mutex; //mutex lock to protect balance

struct ex_arguments{
  int n;       //number of transactions to complete
  int * trans; //reference to the first transaction in the array
};


void * execute( void * args){

  struct ex_arguments * xargs = (struct ex_arguments *) args;
  int i;

  for(i=0;i<xargs->n;i++){
    //TODO: execute all transactions on balance
    // (hint) be mindful of shared memory
    
    pthread_mutex_lock(&mutex);
    balance = balance + xargs->trans[i];
    pthread_mutex_unlock(&mutex);

  }


  //////////////////////////////////////////////////////////////////////
  // DO NOT EDIT 
  //
  //free arguments and return NULL
  free(xargs);
  return NULL;
  //////////////////////////////////////////////////////////////////////
}


int main(){
  //////////////////////////////////////////////////////////////////////
  // DO NOT EDIT
  //
  pthread_t threads[NUM_THREADS];   //array of POSIX thread identifiers
  int transactions[NUM_TRANS];      //array of transactions
  struct ex_arguments * xargs;      //reference for xargs
  int i;                            //for iteration
  int expected_bal = INIT_BALANCE;  //track the expected balance
  //
  pthread_mutex_init(&mutex, NULL); //intitialize the mutex
  //
  srandom(time(NULL));              //seed the random number generator
  //
  //generate an array of random transactions
  for(i=0;i<NUM_TRANS;i++){
    transactions[i] = random() % 100; //random transaction amount
    if(random()%2){ //random credit vs. debit 
      transactions[i] *= -1; //make debits negative
    }
    expected_bal += transactions[i]; //track expected balance
  }
  //////////////////////////////////////////////////////////////////////
  //threads = calloc(NUM_THREADS, sizeof(pthread_t));

  //create threads with well divided work
  for(i=0;i<NUM_THREADS;i++){
    //TODO: Create all threads and pass transac./ion arguments
    //  (hint) : be mindful of shared memory
    xargs->n = NUM_TRANS/NUM_THREADS;
    *xargs->trans = 5000*i;
    pthread_create(&threads[i], NULL, execute, xargs);
  }



  //////////////////////////////////////////////////////////////////////
  // DO NOT EDIT BELOW
  //
  //join all threads
  for(i=0;i<NUM_THREADS;i++){
    pthread_join(threads[i], NULL);
  }
  //
  //report results
  printf(" Balance: %d\n", balance); 
  printf("Exp. Bal: %d\n", expected_bal);
  //
  //cleanup and return
  pthread_mutex_destroy(&mutex);
  return 0;
  //////////////////////////////////////////////////////////////////////
}
