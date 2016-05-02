#include <stdio.h>

int addone(int);

int addone(int a){
  a = a + 1; //different a!
  return a;
}

int main(int argc, char * argv[]){
  int a = 10;
  addone(a);
  printf("%d\n",a); //prints 10! 

  return 0;
}
