#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int count = 0; 
void hand1(int signum){ 
 printf("You Shot Me!\n_"); 
 count++; 
 if(count > 3){ 
 printf("I'm dead.\n"); 
 _exit(1); 
 } 
} 
 
int main(int argc, char * argv[]){ 
 //set up handler 
 //for SIGINT and SIGSTOP 
 signal(SIGINT,handler); 
 signal(SIGSTOP,handler); 
 
 //loop forever 
 while(1); 
}
