#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUF_SIZE 4096

int main(){

  char hostname[]="127.0.0.1";   //localhost ip address to bind to
  short port=1845;               //the port we are to bind to


  struct sockaddr_in saddr_in;  //socket interent address of server
  struct sockaddr_in client_saddr_in;  //socket interent address of client

  socklen_t saddr_len = sizeof(struct sockaddr_in); //length of address

  int server_sock, client_sock;         //socket file descriptor
  
  char response[BUF_SIZE];           //what to send to the client
  int n;
  
  //set up the address information
  saddr_in.sin_family = AF_INET;
  inet_aton(hostname, &saddr_in.sin_addr);
  saddr_in.sin_port = htons(port);

  //open a socket
  if( (server_sock = socket(AF_INET, SOCK_STREAM, 0))  < 0){
    perror("socket");
    exit(1);
  }
  
  //bind the socket
  if(bind(server_sock, (struct sockaddr *) &saddr_in, saddr_len) < 0){
    perror("bind");
    exit(1);
  }

  //ready to listen, queue up to 5 pending connectinos
  if(listen(server_sock, 5)  < 0){
    perror("listen");
    exit(1);
  }


  saddr_len = sizeof(struct sockaddr_in); //length of address

  printf("serer sock listening: (%d)\n",server_sock);

  //accept incoming connections in a loop
  while((client_sock = accept(server_sock, (struct sockaddr *) &client_saddr_in, &saddr_len)) > 0){

    printf("Connection From: %s:%d (%d)\n", 
	   inet_ntoa(client_saddr_in.sin_addr), 
	   ntohs(client_saddr_in.sin_port), 
	   client_sock);


    //echo loop, break when read 0 or error

    while( (n = read(client_sock, response, BUF_SIZE-1)) > 0){
      response[n] = '\0' ; //NULL terminate

      printf("Received From: %s:%d (%d): %s\n",  //LOGGING
	     inet_ntoa(client_saddr_in.sin_addr), 
	     ntohs(client_saddr_in.sin_port), 
	     client_sock, 
	     response);

  
      if(write(client_sock, response, n) < 0){
	perror("write");
	break;
      }
    }
    
    if( n < 0){
      perror("read");
    }
    
    printf("Client Closed: %s:%d (%d)\n",    //LOGGING
	   inet_ntoa(client_saddr_in.sin_addr), 
	   ntohs(client_saddr_in.sin_port), 
	   client_sock);

    //close client socket
    close(client_sock);
    

    //reset socket len just in case
    saddr_len = sizeof(struct sockaddr_in); //length of address
    
  }

  if(client_sock < 0){
    perror("accept");
    exit(1);
  }

  //close the socket
  close(server_sock);

  return 0; //success
}
