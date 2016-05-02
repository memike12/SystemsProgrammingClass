#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

char * clean_comm(char * comm){
  char *p;
  for(p=comm+1;*p;p++){
    if ( *p == ')' ){
      *p = '\0';
      break;
    }
  }
  return comm+1;
}

int main(int argc, char * argv[]){

  pid_t pid, ppid;
  char comm[1024];
  char stat;
  
  int i;
  FILE * stat_f;
  char proc_path[1024];

  if (argc < 2){
    fprintf(stderr, "ERROR: Require a pid to print the satus of\n");
    exit(1);
  }


  printf("PID\tCOMM\tSTATE\tPPID\n");

  for(i = 1 ; i < argc; i ++){


    //TODO: Read from /proc/[pid]/stat and print PID,COMM,STATE,PPID information
    //      see man 5 proc for scanf() formats to use
    //      use clean_comm() to remove '(' and ')' from the command name
   
    //This makes the string for the path I want to open
    snprintf(proc_path, 1024, "/proc/%s/stat", argv[1]);
    
    //Opens the file with the string saved int proc_path. If the process ID dosn't exist,
    //      the program exits
    if ((stat_f = fopen(proc_path, "r")) == NULL){
      fprintf(stderr,"ERROR: fopen: process doesn't exist?\n");
      exit(1);
    }
    
    //Scans in the info that was collected then closes the file    
    fscanf(stat_f, "%d %s %c %d", &pid, comm, &stat, &ppid);
    fclose(stat_f);
    
    //Prints the info that was collected then closes the file 
    printf("%d\t%s\t%c\t%d\n", pid, clean_comm(comm), stat, ppid);

  }

}
