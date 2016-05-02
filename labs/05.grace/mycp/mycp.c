#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <fcntl.h>

#define BUFFSIZE 4096

int main(int argc, char * argv[]){
  
  //Variable Decleartion
  char buf[BUFFSIZE];
  int n, fd_src, fd_dest;
  struct stat fs;


  //TODO: Complete the copy program
  fd_src = open(argv[1], O_RDONLY);
  fd_dest = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
  //fs = stat(argv[1], &fs);
  while ((n = read(fd_src, buf, BUFFSIZE)) > 0)
    if (write(fd_dest, buf, n) != n)
      perror("write error");

  if (n < 0)
    perror("mycp: ERROR $argv[1]" );

  //fchmod(fd_dest, fs.st_mode);
  int close(int fd_src);
  int close(int fd_dest);

  return 0;
}
