#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fun.h"

void bang(char *s){
  char *p;

  for(p = s; *p ; p++){

    if ( *p == 'l'){
      *p = '!';
    }

    if( *p == 'o' ){
      *p = '0';
    }

    if( *p == 'e' ){
      *p = '3';
    }
      
  }

}

