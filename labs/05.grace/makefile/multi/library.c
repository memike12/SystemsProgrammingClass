#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "library.h"

void reverse(char * s){
  char *p,*q, t;
  
  for(p=s, q=(s+strlen(s)-1); p < q; p++, q--){
    t = *p;
    *p = *q;
    *q = t;
  }
  
}
