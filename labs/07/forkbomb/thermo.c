#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){

  int pid, status;
  char ** cmd_argv;
  pid = fork();
  if( pid  == 0 ){
    /* Child */
    
    cmd_argv = argv;
    execvp(cmd_argv[0], cmd_argv);
  }else if (pid > 0){
    /* Parent */
    wait(&status);
    while(1);
  }




}
