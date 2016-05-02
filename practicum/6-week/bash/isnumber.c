#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
  int i;

  //Try a read a number from *stdin*
  if(scanf("%d", &i) == 1){
    return 0; //exit succes, 0, if is a number
  }else{
    return 1; //exit failur, 1, if not a number
  }

}
