#include <stdio.h>
#include <stdlib.h>

#define PAIRS_SIZE 10

typedef struct{
  int left;
  int right;
}pair_t;

//create the pairs array
pair_t ** new_pairs(){
  pair_t ** pairs = (pair_t **) calloc(10, sizeof(pair_t *));
  return pairs;
}

//add a new pair to the pairs array
pair_t * add_pair(pair_t ** pairs, int left , int right){
  int i;
  for(i=0 ; i < PAIRS_SIZE ; i++){
    if(pairs[i] == NULL){
      pairs[i] = malloc(sizeof(pair_t)); //allocate new pair

      pairs[i]->left = left;//do asignment
      pairs[i]->right = right;

      return pairs[i]; //return the new pair
    }
  }  
  return NULL; //list full, return NULL for error
}

//remove a pair at index i
void rm_pair(pair_t ** pairs, int i){
    free(pairs[i]);
    pairs[i] = NULL;
}

//delete all the pairs
void delete_pairs(pair_t ** pairs){
  int i;
  for(i=0; i < PAIRS_SIZE ; i++){
    rm_pair(pairs, i);
  }
  free(pairs);
}

//print all the pairs
void print_pairs(pair_t ** pairs){
  int i;
  for(i=0; i <= PAIRS_SIZE;i++){
      printf("%d: left: %d right: %d\n",i, pairs[i]->left, pairs[i]->right);
  }
}

int main(int argc, char * argv[]){

  pair_t ** pairs = new_pairs(); //create a new pair array

  add_pair(pairs, 2, 10); //assign a new pair
  add_pair(pairs, 0, 3); //assign a new pair
  add_pair(pairs, 13, 7);

  print_pairs(pairs); //print pairs

  rm_pair(pairs, 1); //remove pair at index 1

  printf("------------\n");
  print_pairs(pairs); //print pairs (again)

  delete_pairs(pairs); //delete all pairs, no memleaks!

  return 0;
}
