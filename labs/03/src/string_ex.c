#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strlen() only!

void mystrcpy(char * from, char * to){
  //TODO: Complete the function
  for ( to = from ; *from; from++){
    *to = *from;
  }
}

  void reverse(char * str){
  //TODO: Complete the function
  int ii;
  for(ii =0; ii < strlen(str)/2; ii++)  {
    int temp = str[ii];
    str[ii] = str[(strlen(str)-1)-ii]; 
    str[(strlen(str)-1)-ii] = temp;
  }

}

int main(int argc, char * argv[]){

  char hello[] = "Hello World!";
  char hello_cp[100]; //declared another string of size 100
  
  mystrcpy(hello, hello_cp);
  
  printf("%s\n", hello_cp);
  
  printf("-----------\n");
  
  reverse(hello);
  printf("%s\n",hello_cp); //still print "Hello World!"
  printf("%s\n", hello); //should print "!dlroW olleH"

}
