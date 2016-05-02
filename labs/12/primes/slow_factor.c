#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>


char USAGE[]="./slow_factor n\n"
  "\n"
  " Find a factor the number n or print that its prime\n";

int main(int argc, char * argv[]){

  long n,k,sqn;

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

  //check all values between 2 and the sqrt(n)
  sqn = (long) sqrt(n);

  for(k=2; k <= sqn; k++){
    if( n % k  == 0){
     
      //find a factor and return it
      printf("Factor: %ld\n", k);
      return 0;
    }
  }

  //did not find a factor, it's prime!
  printf("Prime: %ld\n", n);

  return 0;
}
