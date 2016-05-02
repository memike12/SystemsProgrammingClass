#include <stdio.h>
#include <stdlib.h>

int plus(int a,int b){
  int c;

  c = a + b;

  return c;
}

int main(int argc, char * argv[]){
  int a,b,c;
  
  a = 1;
  b = 2;
  c =  plus(1, 2);

  printf("%d\n",c);

  return 0;
}
