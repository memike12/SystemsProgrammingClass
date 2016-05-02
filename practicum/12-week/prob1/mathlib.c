#include <stdio.h>
#include <stdlib.h>

#include "mathlib.h"

int add(int a, int b){
  return a+b;
}

int minus(int a, int b){
  return a-b;
}

int mult(int a, int b){
  return a*b;
}

int divide(int a, int b){
  return a/b;
}

int fact(int a){
  int i,tot = 1;
  if(a <= 0){
    return 0;
  }

  for(i=1;i<=a;i++){
    tot *= i;
  }

  return tot;
}


