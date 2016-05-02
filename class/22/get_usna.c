#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(){

  char hostname[]="usna.edu";    //the hostname we are looking up
  short port=80;                 //the port we are connecting on

  struct addrinfo *result;       //to store results
  struct addrinfo hints;         //to indicate information we want

  struct sockaddr_in *saddr_in;  //socket interent address

  int s,n;                       //for error checking

  int sock;                      //socket file descriptor
  
  char request[]="GET /index.html\n\r"; //the GET request

  char response[4096];           //read in 4096 byte chunks

  
  //setup our hints
  memset(&hints,0,sizeof(struct addrinfo));  //zero out hints
  hints.ai_family = AF_INET; //we only want IPv4 addresses

  //Convert the hostname to an address
  if( (s = getaddrinfo(hostname, NULL, &hints, &result)) != 0){
    fprintf(stderr, "getaddrinfo: %s\n",gai_strerror(s));
    exit(1);
  }

  //convert generic socket address to inet socket address
  saddr_in = (struct sockaddr_in *) result->ai_addr;
  
  //set the port in network byte order
  saddr_in->sin_port = htons(port);

  //open a socket
  if( (sock = socket(AF_INET, SOCK_STREAM, 0))  < 0){
    perror("socket");
    exit(1);
  }

  //connect to the server
  if(connect(sock, (struct sockaddr *) saddr_in, sizeof(*saddr_in)) < 0){
    perror("connect");
    exit(1);
  }

  //send the request
  if(write(sock,request,strlen(request)) < 0){
    perror("send");
  }

  //read the response until EOF
  while( (n = read(sock, response, 4096)) > 0){

    //write response to stdout
    if(write(1, response, n) < 0){
      perror("write");
      exit(1);
    }
  }

  if (n<0){
    perror("read");
  }
  
  //close the socket
  close(sock);

  return 0; //success
}
