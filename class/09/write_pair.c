#include <unistd.h>
#include <stdio.h>

typedef struct{
  int left;
  int right;
} pair_t;

int main(int argc, char * argv[]){

  pair_t p;
  p.left = 10;
  p.right = 20;

  write(1, &p, sizeof(pair_t));
}
   
