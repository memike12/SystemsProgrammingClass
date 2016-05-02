#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <arpa/inet.h>


int main(){

  //in_addr struct has a single member s_addr
  struct in_addr addr;

  //Convert the string directly 
  inet_pton(AF_INET, "10.4.32.41", &(addr.s_addr));

  printf("Hello %s\n", inet_ntoa(addr));
  
}
