#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[]){
  char hello[] = "Say Hello\n";
  char said[] = "You said: ";
  char response[10];
  int n;

  do{

    write(1, hello, strlen(hello));
    n = read(0, response, 10);

    write(1, said, strlen(said));
    write(1, response, 10);
  }while( n !=  0);

  return 0;
}
