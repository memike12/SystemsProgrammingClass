#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){

  int fd, status;
  pid_t cpid;
  char c;

  if ( argc < 2){
    fprintf(stderr, "ERROR: Require path\n");
    return 1;
  }

  if( (fd = open(argv[1], O_RDONLY)) < 0){
    perror("open");
    return 1;
  }

  while (1){

    cpid = fork();
    
    if( cpid == 0 ){
      /* CHILD */
      
      //try and read 1 byte from file
      if( read(fd, &c, 1) > 0){
	printf("c: %c\n", c); // print the char

	_exit(0); //exit with status 0 on sucess read
      }else{
	//no more to read
	_exit(1); //exit with status 1 on failed read
      }

    }else if ( cpid > 0){
      /* PARENT */
    
      //wait for child to read first
      wait(&status);
      
      //if exit status 1, break the loop, no more to read
      if( WEXITSTATUS(status) ){
	break; 
      }
      
      //now parent reads a byte
      if( read(fd, &c, 1) > 0){
	printf("p: %c\n", c); // print the char
      }
      
    }else{
      /* ERROR */
      perror("fork");
      return 1;
    }
  }

  //done reading the file
  close(fd);

  return 0;
}
