#include <unistd.h>

int main(int argc, char * argvp[]){
  char *p;
  char hello[] = "Hello World!\n";

  for(p=hello; *p; p++){
    write(1, p, 1);
  }
}
