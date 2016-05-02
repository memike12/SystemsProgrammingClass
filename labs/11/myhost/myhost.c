#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[]){

  struct addrinfo *result;    //to store results
  struct addrinfo *cur_result;    //to store results

  struct addrinfo hints;      //to indicate information we want

  struct sockaddr_in *saddr;  //to reference address
  struct sockaddr_in6 *saddr6;  //to reference address

  int s; //for error checking


  //TODO: Complete the lab
  //
  // Outline:
  //   - set up the hints
  //   - perform the getaddrinfo()
  //   - iterate the results
  //   - print the resolved ip address
  //   - cleanup the results with freaddrinfo(result)
  memset(&hints,0,sizeof(struct addrinfo));  //zero out hints
  hints.ai_family = AF_INET; //we only want IPv4 addresses

  //Convert the hostname to an address
  if( (s = getaddrinfo(argv[1], NULL, &hints, &result)) != 0){
    fprintf(stderr, "getaddrinfo: %s\n",gai_strerror(s));
    exit(1);
  }
  for(cur_result = result; cur_result != NULL; cur_result = cur_result->ai_next){
    //do something with the current result
    saddr = (struct sockaddr_in *) cur_result->ai_addr;
    if (cur_result->ai_protocol == IPPROTO_TCP){
      printf("%s has address %s\n", argv[1],inet_ntoa(saddr->sin_addr));
    }
    
  }
  //free the addrinfo struct
  freeaddrinfo(result);
  
  return 0; //success
}
