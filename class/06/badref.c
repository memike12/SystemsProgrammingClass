#include <stdio.h>
#include <stdlib.h>

int * plus(int a, int b){
  int c = a + b;
  return &c;    // on return c is freed
}

int main(int argc, char * argv[]){
  int * c = plus(1,2);
  printf("%d\n",*c); //this might work

  c = plus(*c, *c); //this will likely fail
  printf("%d\n",*c);
}
