#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

int main(){
  char s[10];
  double t = 0.0, x;

  while(fscanf(stdin,"%s",s) == 1){
    if (isdigit(s[0]))
      t += sin(atoi(s));    
  }
  
  fprintf(stdout,"%f\n",t);

  return 0;
}
