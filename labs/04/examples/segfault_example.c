#include <stdio.h>
#include <stdlib.h>

void foo(){
  char str[10];
  printf("Enter String:\n");
  scanf("%s", str);
}
int main(int argc, char *argv[]){
  foo();
}

