#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

/**
 * timeval_subtract : subtract timeval x - y and store result in result
 **/
int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y) {
   /* Perform the carry for the later subtraction by updating y. */
   if (x->tv_usec < y->tv_usec) {
     int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
     y->tv_usec -= 1000000 * nsec;
     y->tv_sec += nsec;
   }
   if (x->tv_usec - y->tv_usec > 1000000) {
     int nsec = (x->tv_usec - y->tv_usec) / 1000000;
     y->tv_usec += 1000000 * nsec;
     y->tv_sec -= nsec;
   }
     
   /* Compute the time remaining to wait.
      tv_usec is certainly positive. */
   result->tv_sec = x->tv_sec - y->tv_sec;
   result->tv_usec = x->tv_usec - y->tv_usec;
     
   /* Return 1 if result is negative. */
   return x->tv_sec < y->tv_sec;
 }

int main(int argc, char * argv[]){

  int status;
  pid_t c_pid;
  struct timeval start, end, diff;

  //TODO: complete fork-exec-wait and time the result
  //
  // use this print statement to output the reslts once you've
  // calcualted the time of execution
  //    printf("Run Time: %ld.%04ld (s)\n", diff.tv_sec, diff.tv_usec/1000);
  //
  // To calculate the difference between two timevals:
  //    timeval_subtract(&result, &end, &start)
  gettimeofday(&start, 0);
  c_pid = fork();
  if (c_pid == 0){
    /* CHILD */

    //printf("Child: executing ls\n");

    //execute ls            
    argv = argv+1;
    execvp( argv[0], argv);
    //only get here if exec failed                                                                                                                                             
    perror("execve failed");
  }else if (c_pid > 0){
    /* PARENT */

    if( (c_pid = wait(&status)) < 0){
      perror("wait");
      _exit(1);
    }
    gettimeofday(&end, 0);
    //printf("Parent: finished\n");

  }else{
    perror("fork failed");
    _exit(1);
  }

  timeval_subtract(&diff, &end, &start);
  printf("Run Time: %ld.%04ld (s)\n", diff.tv_sec, diff.tv_usec/1000);
  return 0;
}

