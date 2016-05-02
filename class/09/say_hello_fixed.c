#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[]){
  char hello[] = "Say Hello\n";
  char said[] = "You said: ";
  char response[10];
  int n;

  do{

    write(1, hello, strlen(hello));

    n = read(0, response, 9); //<-- needs to be null terminated
    response[n] = '\0'; 

    write(1, said, strlen(said));
    write(1, response, n-1); //<--- only write the size of the buffer
    write(1, "\n", 1); //<--- extra newline for pritty printing

  }while( n !=  0);

  return 0;
}
