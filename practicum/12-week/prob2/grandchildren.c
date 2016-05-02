#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

  //DO NOT EDIT
  char * cmd[] = {"cat", NULL};
  int cpid;
  int pfd_1[2] = {-1,-1} ,pfd_2[2] = {-1,-1};
  char c;

  //TODO: add neccesary pipeline code
  if ( pipe(pfd_1) < 0){
    perror("pipe");
    return 1;
  }

  if ( pipe(pfd_2) < 0){
    perror("pipe");
    return 1;
  }
  
  if( (cpid = fork()) ) {
    /* CHILD 1 */

    //TODO: add neccesary pipeline code
    close(0);
    close(1);
    dup2(pfd_1[0], 0);
    dup2(pfd_2[1], 1);



    if( (cpid = fork()) ) {
      /* CHILD 2*/

      //TODO: add neccesary pipeline code
      
      close(0);

      //duplicate reading end to stdin
      dup2(pfd_2[0], 0);

      //close the writing end
      close(pfd_2[1]);




      //DO NOT EDIT/////////////////////////
      //read from pfd_2 and write to stdout
      while(1){
	if(read(pfd_2[0],&c,1) > 0){
	  write(1,&c,1);
	}else{
	  exit(0);
	}
      }
      ////////////////////////////////////

    }else if(cpid == 0){
      /* CHILD 1 */


      //TODO: add neccesary pipeline code
      close(pfd_2[0]);
    
      //close(pfd_2[1]);
      close(0);
      close(1);

      //DO NOT EDIT/////////////////////////
      //read from pfd_1 and write to pfd_2
      while(1){
	if(read(pfd_1[0],&c,1) > 0){
	  write(pfd_2[1],&c,1);
	}else{
	  exit(0);
	}
      }
      ////////////////////////////////////
    }      

  }else if(cpid == 0){
    /* PARENT */

    //close stdout should duplicate pipe onto it
    close(1);

    //TODO: add neccesary pipeline and duplication
    dup2(pfd_1[1], 1);

    close(pfd_1[0]);
   
   
    //DO NOT EDIT/////////////////////////
    //execute the cat command
    execvp(cmd[0], cmd);
    perror("exec failure");
    _exit(1);
    ////////////////////////////////////
  }

}
