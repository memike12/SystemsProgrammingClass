#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
  int n,i;

  printf("How many ints?\n");
  scanf("%d",&n);

  int array[n];

  for(i=0;i<n;i++){
    scanf("%d", &(array[i]));
  }

  for(i=0;i<n;i++){
    printf("%d ",array[i]);
  }
  printf("\n");
}
