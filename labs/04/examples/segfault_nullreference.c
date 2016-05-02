#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int left;
  int right;
}pair_t;

int main(int argc, char *argv[]){
  int i;
  pair_t ** pairs = calloc(10, sizeof(pair_t *));

  for(i = 0 ; i < 10; i++){
    pairs[i] = malloc(sizeof(pair_t));
    pairs[i]->left = i;
    pairs[i]->right = i+1;
  }

  //...
  free(pairs[2]);
  pairs[2] = NULL;
  //...

  for(i=0 ; i < 10; i++){
    printf("%d: left: %d right: %d\n", i, pairs[i]->left, pairs[i]->right);
  }

  return 0;
}
