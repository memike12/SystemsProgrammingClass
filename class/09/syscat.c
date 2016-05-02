#include <unistd.h>

#define BUFSIZE 1

/**
 * cat like command that reads from stdin and writes to stdout
 **/
int main(int argc, char * argv[]){
  int n;
  char buf[BUFSIZE];
  
  while( (n = read(0, buf, BUFSIZE)) != 0){
    
    write(1, buf, n);
    
  }

}
