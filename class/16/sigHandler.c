#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int count = 0; 
void handler(int signum){ 
 printf("You Shot Me!\n_"); 
 count++; 
 if(count > 3){ 
 printf("I'm dead.\n"); 
 _exit(1); 
 } 
} 
 
int main(){ 
 //set up handler 
 //for SIGINT and SIGSTOP 
 signal(SIGINT,handler); 
 signal(SIGSTOP,handler); 
 
 //loop forever 
 while(1); 
} 
