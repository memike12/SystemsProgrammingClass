#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>

//THE TODO IS TOWARDS THE BOTTOM
// This code above is for setting up the listening socket and addressing
// your task it complete the code when a new client connects to the proxy


//////////////////////////////////////////////////////////////////////
// DO NOT EDIT 

#define BUF_SIZE 4096

int server_sock = 0;

void exit_handler(void){
  printf("Closing Socket\n");
  close(server_sock);
}

void _exit_handler(int sig){
  exit(1);
}
//////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[]){

//////////////////////////////////////////////////////////////////////
// DO NOT EDIT 

  char hostname[]="127.0.0.1";   //localhost ip address to bind to
  short port=1845;               //the port we are to bind to

  struct addrinfo hints;        //for hints of getaddrinfo()
  struct addrinfo * result;      //for results of getaddrinfo()
  int s;

  struct sockaddr_in server_saddr_in;  //socket interent address of server
  struct sockaddr_in client_saddr_in;  //socket interent address of client
  struct sockaddr_in proxy_saddr_in;  //address of remote address to proxy to 

  socklen_t saddr_len = sizeof(struct sockaddr_in); //length of address

  int client_sock, proxy_sock; //socket file descriptors

  int n;                 //for read/write
  char buf[BUF_SIZE];   //bufer for read/write

  //some exit handling
  atexit(exit_handler);
  signal(SIGSEGV,_exit_handler);
  signal(SIGINT,_exit_handler);
  signal(SIGTERM,_exit_handler);
  
  //ERROR CHECKING

  if(argc < 3){
    fprintf(stderr, "ERROR: Require host and port to proxy to\n");
    exit(1);
  }

  if(atol(argv[2]) == 0){
    fprintf(stderr, "ERROR: Invalid port number '%s'\n", argv[2]);
    exit(1);
  }

  //DESTINATION ADDRESS INFORMATION
  //setup our hints
  memset(&hints,0,sizeof(struct addrinfo));  //zero out hints
  hints.ai_family = AF_INET; //we only want IPv4 addresses

  //Convert the hostname to an address
  if( (s = getaddrinfo(argv[1], NULL, &hints, &result)) != 0){
    fprintf(stderr, "getaddrinfo: %s\n",gai_strerror(s));
    exit(1);
  }

  //convert generic socket address to inet socket address
  proxy_saddr_in = *((struct sockaddr_in *) result->ai_addr);
  
  //set the port in network byte order
  proxy_saddr_in.sin_port = htons(atol(argv[2]));


  //SETUP SERVER  
  server_saddr_in.sin_family = AF_INET;
  server_saddr_in.sin_port = htons(port);
  inet_aton(hostname, &(server_saddr_in.sin_addr));
  
  //open socket
  if( (server_sock = socket(AF_INET, SOCK_STREAM, 0))  < 0){
    perror("socket");
    exit(1);
  }

  //bind the socket
  if(bind(server_sock, (struct sockaddr *) &server_saddr_in, saddr_len) < 0){
    perror("bind");
    exit(1);
  }

  //ready to listen, queue up to 5 pending connectinos
  if(listen(server_sock, 5)  < 0){
    perror("listen");
    exit(1);
  }
  //////////////////////////////////////////////////////////////////////

  //ACCEPT INCOMING CONNECTIONS
  saddr_len = sizeof(struct sockaddr_in); //length of address
  while((client_sock = accept(server_sock, (struct sockaddr *) &client_saddr_in, &saddr_len)) > 0){

    printf("Connection From: %s:%d (%d)\n", 
           inet_ntoa(client_saddr_in.sin_addr), 
           ntohs(client_saddr_in.sin_port), 
           client_sock);
    
    //TODO: Complete the proxy
    // (1) Open a proxy socket and connect to the foreign address (use print statement below
    // (2) Read request from client socket
    // (3) Write request to proxy socket
    // (4) Read ENTIRE response from proxy socket and write to client socket
    // (5) Close proxy and client socket
    //
 //open socket
    if( (proxy_sock = socket(AF_INET, SOCK_STREAM, 0))  < 0){
    perror("socket");
    exit(1);
  }

  //bind the socket
  if(bind(proxy_sock, (struct sockaddr *) &proxy_saddr_in, saddr_len) < 0){
    perror("bind");
    exit(1);
  }

    //
    // Use this print statement once the proxy socket is open and conncted
    //
     printf("Proxy to: %s:%d (%d)\n",  
            inet_ntoa(proxy_saddr_in.sin_addr),  
            ntohs(proxy_saddr_in.sin_port),  
            proxy_sock); 

    

  }


  ///////////////////////////////////////////////////////////////////////////////////////////////
  //DO NOT EDIT BELOW
  
  close(server_sock);
  return 0;
}
