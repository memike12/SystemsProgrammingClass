#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>

int main(int argc, char * argv[]){
  
  char smode[12]; //mode strings are always 11 chars long
                  // +1 for the NULL, makes 12!
  
  strmode(0644, smode);
  printf("0644 : %s\n", smode);

  strmode(0742, smode);
  printf("0742 : %s\n", smode);

}
