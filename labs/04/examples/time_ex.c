#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char * argv[]){
  time_t ts = time(NULL); //time stamp
  printf("%s", citme(&ts)); //print as string
                            //formates with new line
}
