#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[]){

  int a,b,*p;

  float perc = 0.2005;

  p = &b;
  *p = 15; /* (1) */
  printf("%0.2f, &perc %%");
printf("a:%d\n",a);
  printf("b:%d\n",b);
  printf("*p:%d\n",*p);

  a = b;
  b = 25; /* (2) */

 printf("a:%d\n",a);
  printf("b:%d\n",b);
  printf("*p:%d\n",*p);

  p = &a; /* (3) */

 printf("a:%d\n",a);
  printf("b:%d\n",b);
  printf("*p:%d\n",*p);

  (*p)++; /* (4) */

  printf("a:%d\n",a);
  printf("b:%d\n",b);
  printf("*p:%d\n",*p);
  printf("Size of short: %lu bytes\n", sizeof(short));
  printf("Size of int: %lu bytes\n", sizeof(int));
}
