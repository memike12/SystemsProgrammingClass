#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[]){

  //variable decleration
  struct stat sb;
  struct timeval tv[2];

  //TODO: Complete the touch operation
  // if(stat(argv[1], &sb) == NULL){
  //  fprintf(stderr, "ERROR: diropen: %s\n", strerror(errno));
  //  return 1;
  //}

  //stat(argv[1], &sb);
  
  gettimeofday(tv, NULL);

  printf("Last Modified: %s", ctime(&(tv->tv_sec)));

  utimes(argv[1], &tv[2]);
  gettimeofday(tv, NULL);
  printf("New Modified: %s", ctime(&(tv->tv_sec)));
  return 0;
}

