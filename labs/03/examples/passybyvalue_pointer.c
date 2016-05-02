#include <stdio.h>

void addone(int *);

void addone(int *p){ //takes a pointer to a
  *p = *p + 1;
  return;
}

int main(int argc, char * argv[]){
  int a = 10;
  addone(&a); //pass the address of a
  printf("%d\n",a); //prints 11! 
  
  return 0;
}
