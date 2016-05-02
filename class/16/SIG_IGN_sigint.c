#include <signal.h>
#include <sys/signal.h>

int main(){
  
  signal(SIGINT, SIG_IGN);

  while(1);
}
