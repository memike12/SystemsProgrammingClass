#include <signal.h>
#include <sys/signal.h>

void nothing(int signum){ /*DO NOTHING*/ }
int main(){
  
  signal(SIGINT, nothing);

  while(1);
}
