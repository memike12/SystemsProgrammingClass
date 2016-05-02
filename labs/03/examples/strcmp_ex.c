#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strcmp

int main(int argc, char * argv[]){
  char s1[] = "Hello";
  char s2[] = "Goodbye";
  char s3[] = "Igloo";

  //strcmp returns 0 when the two strings are equal
  if( 0 == strcmp(s1,s1)){
    printf("s1 == s1\n");
  }
  
  if( 0 != strcmp(s1,s2)){
    printf("s1 != s2\n");
  }

  //strcmp returns a number indicate sorting order of strings
  printf("s1 > s2 : %d\n", strcmp(s1,s2));
  printf("s2 < s1 : %d\n", strcmp(s2,s1));
  printf("s2 < s3 : %d\n", strcmp(s2,s3));
  printf("s3 > s1 : %d\n", strcmp(s3,s1));
  
  return 0;
}
