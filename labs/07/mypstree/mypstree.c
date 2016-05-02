#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio_ext.h>

///////////////////////////////////////////////////////////
// DO NOT EDIT BELOW


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

///////////////////////////////////////////////////////////
// *DO* EDIT BELOW



int getparent(pid_t parent, int depth){
  pid_t pid, ppid;
  char comm[1024];
  char state[2];
  FILE * stat_f;
  char proc_path[1024];
  int max_depth,i;

  //reached the kernel, return how far we've come
  if(parent == 0){
    return depth;
  }

  //TODO: READ from stat recursively call getparent() from
  //      child-to-parent-to-grandparent-to...-to-init 
  //     
  //      Will return the max-depth, the length of tbe path to init

  else{
    
    snprintf(proc_path, 1024, "/proc/%d/stat", parent);
    if ((stat_f = fopen(proc_path, "r")) == NULL){
      fprintf(stderr,"ERROR: fopen: process doesn't exist?\n");
      exit(1);
    }
    fscanf(stat_f, "%d %s %c %d", &pid, comm, &state, &ppid);
    depth ++;
    max_depth = getparent(ppid, depth);
    
    printf("%s\n", clean_comm(comm));

    //space in based on the current depth and max_depth
    for(i=depth;i<max_depth;i++){
      printf("  "); //print a space for each depth
    }
    if(depth > 1){
      printf("└─"); //nice symbol
    }
  }


  //return the max_depth
  return max_depth;
}


///////////////////////////////////////////////////////////
// DO NOT EDIT BELOW

int main(int argc, char * argv[]){

  pid_t pid;
  
  int i;

  if (argc < 2){
    fprintf(stderr, "ERROR: Require a pid to print the satus of\n");
    exit(1);
  }

  for(i = 1 ; i < argc; i++){
    if(sscanf(argv[i],"%d",&pid) == 0){
      fprintf(stderr, "ERROR: Invalid pid %s\n", argv[i]);
      continue;
    }
    getparent(pid,0);

    printf("\n");
  }

  

}
