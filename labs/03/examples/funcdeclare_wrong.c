#include <stdio.h>

int addtwo(int a){
  return addone(addone(a)); //addone() hasn't been declared yet
}

int addone(int a){
  return a+1;
}

int main(int argc, char *argv[]){
  printf("%d\n", addtwo(10)); //prints 12
}
