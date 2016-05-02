#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void print_bits(unsigned int a){
  unsigned int mask =  1 << (sizeof(int)*8-1);
  int i;

  for(i=0;i < sizeof(int)*8; i++, mask >>= 1){
    if( a & mask){
      printf("1");
    }else{
      printf("0");
    }
  }
  
  printf("\n");
}

int main(int argc, char * argv[]){

  print_bits(O_WRONLY);
  print_bits(O_TRUNC);
  print_bits(O_CREAT);
  printf("--------------------------------- OR\n");
  print_bits(O_WRONLY | O_TRUNC | O_CREAT);

}
