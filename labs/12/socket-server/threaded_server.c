#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <pthread.h>

#define BUF_SIZE 4096
struct server_args{
  struct sockaddr_in addr;
  int sock;
};
void * client_handler(void * args){
  //TODO: Complete the client handler
  //
  // HINT: Consider what arguments need to be passed to client handler
  //       to print the right info.
  //
  // Output print statements:
  //
  //   printf("Received From: %s:%d (%d): %s", inet_ntoa(client_saddr_in.sin_addr),
  //           ntohs(client_saddr_in.sin_port), client_sock, response);
  //
  //    printf("Received From: %s:%d (%d): %s", inet_ntoa(client_saddr_in.sin_addr),
  //            ntohs(client_saddr_in.sin_port), client_sock, response);
  struct server_args * sargs = (struct server_args *) args;
  char response[BUF_SIZE];
  int n;
  while( (n = read(sargs->sock, response, BUF_SIZE-1)) > 0){
      response[n] = '\0' ; //NULL terminate

      printf("Received From: %s:%d (%d): %s\n",  //LOGGING
	     inet_ntoa(sargs->addr.sin_addr), 
	     ntohs(sargs->addr.sin_port), 
	     sargs->sock, 
	     response);

      if(write(sargs->sock, response, n) < 0){
	perror("write");
	break;
      }
    }

   printf("Client Closed: %s:%d (%d)", inet_ntoa(sargs->addr.sin_addr),
             ntohs(sargs->addr.sin_port), sargs->sock);
   return (void *) *response;
}

int main(){
  //TODO: Complete the main function
  //
  // HINT: When you start a thread, you should detach it so that you
  //       do not have to join it later. Use: pthread_detach()
  char hostname[]="127.0.0.1";   //localhost ip address to bind to
  short port=1845;   //the port we are to bind to

  struct sockaddr_in saddr_in;  //socket interent address of server
  struct sockaddr_in client_saddr_in;  //socket interent address of client
  
  socklen_t saddr_len = sizeof(struct sockaddr_in); //length of address

  int server_sock, client_sock;         //socket file descriptor
          
 
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

  printf("server sock listening: (%d)\n",server_sock);

  //accept incoming connections in a loop
 

  while(1){ //loop

    while((client_sock = accept(server_sock, (struct sockaddr *) &client_saddr_in, &saddr_len)) > 0){

      printf("Connection From: %s:%d (%d)\n", 
             inet_ntoa(client_saddr_in.sin_addr), 
             ntohs(client_saddr_in.sin_port), 
             client_sock);
      pthread_t thread;
      struct server_args* args = malloc(sizeof(struct server_args));
      args->sock = client_sock;
      args->addr = client_saddr_in;
      
      pthread_create(&thread, NULL, client_handler, args);
      pthread_detach(thread);
    }    
  }

  if(client_sock < 0){
    perror("accept");
    exit(1);
  }
  //close the socket
  close(server_sock);

  return 0; //success
}
