#include <stdio.h>

int addone(int); //declaring the prototype of addone()
int addtwo(int); //declaring the prototype of addtwo()

int addtwo(int a){
  return addone(addone(a)); //addone() is now known here
}

int addone(int a){
  return a+1;
}

int main(int argc, char *argv[]){
  printf("%d\n", addtwo(10)); //prints 12
}
