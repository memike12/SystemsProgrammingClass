#include <stdio.h>
#include <stdlib.h>

int main(){
  char str[10];
  fscanf(stdin, "%s", str);
  fprintf(stdout, "You said: `%s' \n", str);

  return 0;
}
