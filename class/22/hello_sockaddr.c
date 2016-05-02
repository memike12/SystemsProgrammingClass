#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <arpa/inet.h>


int main(){

  
  //use a generic socket address to store everything
  struct sockaddr saddr;
  
  //cast generic socket to an inet socket
  struct sockaddr_in * saddr_in = (struct sockaddr_in *) &saddr;
  
  //Convert IP address into inet address stored in sockaddr
  inet_aton("10.4.32.41", &(saddr_in->sin_addr));

  //print out IP address
  printf("Hello %s\n", inet_ntoa(saddr_in->sin_addr));
  
}
