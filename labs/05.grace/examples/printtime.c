#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char * argv[]){

  struct timeval tv;
  
  gettimeofday(&tv,NULL);

  //ctime takes a pointer to the second
  printf("%s", ctime(&(tv.tv_sec)));

}
