#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char * argv[]){

  int fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
  
  close(fd);

}
