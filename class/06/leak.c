#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]){
  int i, * p;

  for(i=0;i>100;i++){
    p = (int *) malloc(sizeof(int));
    *p = i;
  }
  
}
