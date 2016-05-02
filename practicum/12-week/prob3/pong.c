#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//TODO: Complete the signal handler
//
//   * The arguments to the signal handler function depend on the type
//     of handler, e.g., a basic handler or one that requires a
//     siginfo

void handler(int signum, siginfo_t * siginfo, void * context){
  for(int i =0; i < 100; i++){
    if( siginfo->si_code == i){
      printf("pong %d\n", siginfo->si_code);
      break;
    }
  }
  if( WIFEXITED(siginfo->si_status) ){
    printf("terminated and exited with status %d\n", WEXITSTATUS(siginfo->si_status));
  }

  fflush(stdout);

  exit(0); //DO NOT EDIT
}

int main(int argc, char * argv[]){
  
  //DO NOT EDIT///////////////////////////////////
  pid_t cpid; //child pid
  char * cmd_ping[] = {"./ping", NULL}; //cmd_argv
  int i; //iterator
  ////////////////////////////////////////////////
  
  //TODO: Setup signal handler
  //
  //   * Will need to handle potentiall all signals, except SIGCHLD,
  //     SIGKILL, and SIGSTOP
  //
  //   * Will probably need to use sigaction() insted of signal() to
  //     establish the handler, may want siginfo data
  int signum;

  struct sigaction action;
  action.sa_sigaction = handler;
  action.sa_flags = SA_RESTART | SA_SIGINFO;
  
  sigaction(SIGCHLD, &action, NULL);



  

  //DO NOT EDIT///////////////////////
  if( (cpid = fork()) == 0 ){
    /* CHILD */
    execvp(cmd_ping[0], cmd_ping);
    perror("exec");
    exit(2);
  }else{
    /* PARENT */
    wait(NULL);
  }
  return 0;
  //////////////////////////////////
}
