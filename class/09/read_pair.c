#include <unistd.h>
#include <stdio.h> //format print

typedef struct{
  int left;
  int right;
} pair_t;

int main(int argc, char * argv[]){

  pair_t p;

  read(0, &p, sizeof(pair_t));

  printf("left: %d right: %d\n",p.left, p.right);
}
   
