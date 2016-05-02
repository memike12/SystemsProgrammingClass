#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char * argv[]){
  
  int fd = open("print_descriptor.c", O_RDONLY);

  printf("fd: %d\n", fd);

  close(fd);
}
