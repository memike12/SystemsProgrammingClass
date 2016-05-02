#include <unistd.h>

#include <string.h> //strlen()

int main(int argc, char *argv[]){
  char hello[] = "Hello World\n";

  write(1, hello, strlen(hello));

}
