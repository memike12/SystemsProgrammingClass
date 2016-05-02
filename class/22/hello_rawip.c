#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <arpa/inet.h>


int main(){

  //in_addr struct has a single member s_addr
  struct in_addr addr;
  unsigned char * ip;

  //have ip point to s_addr
  ip = (unsigned char *) &(addr.s_addr);
  
  //set the bytes
  ip[0]=10;
  ip[1]=4;
  ip[2]=32;
  ip[3]=41;

  //print it out
  printf("Hello %s\n", inet_ntoa(addr));
  
}
