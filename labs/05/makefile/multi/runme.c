#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "library.h"

int main(int argc, char * argv[]){
  
  char s[] = "Hello World!";

  printf("%s\n", s);

  reverse(s);

  printf("%s\n", s);

}
