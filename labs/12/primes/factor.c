#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

char USAGE[]="./factor n\n"
  "\n"
  " Find a factor for the number n using threads or print that its prime\n";



#define MAX_THREADS 4


int       running[MAX_THREADS];     //track which threads are running,
                                    // 0 for not 1 for yes

pthread_t threads[MAX_THREADS];     //track thread information

//struct to pass arguments to factor
struct factor_args{
  long start; //start of range
  long end;   //end with this factor
  long n;     //number to factor
  int i;      //thread number
};


//The factor function
void * factor(void * args){
  //cast the factor
  struct factor_args * fargs = (struct factor_args *) args;
  long * result = malloc(sizeof(long));
  *result = -1;
  //TODO: complete the factor functoin
  // 
  // Check for a factor between start and end, return it if found,
  // otherwise return -1
  //
  // HINT: Be sure to return a result allocated on the heap!
  if (fargs->end == 0)
    return (void *) result;
  for(long k=fargs->start; k <= fargs->end; k++){
    if( fargs->n % k  == 0){
      //find a factor and return it
      *result = k;
      running[fargs->i]=0; //set not running
      return (void *) result;
    }
  }
  running[fargs->i]=0; //set not running
  return (void *) result;
}

int main(int argc, char * argv[]){

  long n;        //the number to factor
  //long start;    //the start factor for dividing work
  //long span;     //the span of factors for dividing work
  long * result; //for retrieving results from a thread
  int i;         //iterator

  struct factor_args * fargs; //pointer for allocator factor aguments

  //check for right number of arguments
  if(argc < 2){
    fprintf(stderr, "ERROR: require n\n%s",USAGE);
    exit(1);
  }

  //convert to a long
  n = atol(argv[1]);
  
  
  //check for rigth format
  if( n == 0){
    fprintf(stderr, "ERROR: invalid value for n\n%s",USAGE);
    exit(1);

  }
  
  //initialize all threads to not running
  for(i=0 ; i < MAX_THREADS; i++){
    running[i] = 0;
  }
 

  //TODO: Complete the program
  //
  // outline:
  // (1) Divide the work up so that each thread checks a different set
  // of factors: e.g.,
  //   [2,sqrt(n)/MAX_THREADS],
  //   (sqrt(n)/MAX_THREADS,2*sqrt(n)/MAX_THREADS]
  //   (2*sqrt(n)/MAX_THREADS,3*sqrt(n)/MAX_THREADS]
  //   etc.
  // (2) spawn each thread based
  // (3) Check for threads running state
  // (4) if not running, join and see if they found a factor
  // (5) if factor found, then print to screen and exit
  // (6) if no threads are running and no factor found, report that
  //     the number is prime and exit
  //
  // HINT: Don't forget to set thread running when you start it with running[i]=1
  // HINT: You'll need to write a loop to continually check the running state of threads
  fargs = NULL;
  for( i= 0; i < MAX_THREADS; i++){
    if(i==0){
      struct factor_args  * fargs = (struct factor_args*) malloc(sizeof(struct factor_args)); 
      fargs->start = 2;
      fargs->end = ceill(sqrt(n)/MAX_THREADS);
      fargs->n = n;
      fargs->i = i;
      pthread_create(&threads[0], NULL, factor, fargs);
    }
    else{
      struct factor_args  * fargs = (struct factor_args*) malloc(sizeof(struct factor_args)); 
      fargs->start = ceill(i*sqrt(n)/MAX_THREADS) +1;
      fargs->end = ceill((i+1)*sqrt(n)/MAX_THREADS);
      fargs->n = n;
      fargs->i = i;
      pthread_create(&threads[i], NULL, factor, fargs);
    }
    running[i] = 1;
  }
  for( i=0; i < MAX_THREADS; i++){
    while(running[i]!=0);
    pthread_join(threads[i], &result);
    result = (long *) result;
    if(*result > 0){
      printf("Factor: %ld\n", *result);
      exit(0);
    }
  }
  printf("Prime: %ld\n", n);
  return 0;
}


