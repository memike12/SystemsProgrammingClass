#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>


int main(){ 
  alarm(1); 

        alarm(2); 
       alarm(3); 
       alarm(4); 
 pause(); 
}
