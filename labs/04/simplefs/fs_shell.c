#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include <readline/readline.h>
#include <readline/history.h>


#include "filesystem.h"


int main(int argc, char * argv[]){

  dir_t * curdir = NULL;
  char * line, * tok, *arg;


  rl_bind_key('\t', rl_abort);

  while(1){

    
    //read input
    if (curdir == NULL){
      line = readline("fs_shell (-) > ");
    }else{
      line = readline("fs_shell (*) > ");
    }

    //EOF reached
    if( line == NULL){

      if (curdir){
	myfs_rmdir(curdir); //clean up
      }

      printf("\n");
      break;
    }


    //empty line, continue
    if(0 == strtok(line, "")){
      continue;
    }

    //add line to history
    add_history(line);


    //cut based on " " 
    tok = strtok(line, " ");


    //check to see if it matches a command
    if ( 0 == strcmp(tok, "mkdir")){

      if( curdir != NULL){
	fprintf(stderr, "ERROR: curdir set: call rmdir\n");
      }else{
	curdir = myfs_mkdir();
      }

    }else if ( 0 == strcmp(tok, "rmdir")){

      if( curdir == NULL){
	printf("ERROR: curdir not set: call mkdir\n");
      }else{
	myfs_rmdir(curdir);
	curdir = NULL;
      }
      
    }else if (0 == strcmp(tok, "ls")){
      if( curdir == NULL){
	fprintf(stderr, "ERROR: curdir not set: call mkdir\n");
      }else{
	myfs_ls(curdir);
      }
    }else if (0 == strcmp(tok, "ltime")){
      if( curdir == NULL){
	fprintf(stderr,"ERROR: curdir not set: call mkdir\n");
      }else{
	myfs_ls_sorttime(curdir);
      }
    }else if (0 == strcmp(tok, "lname")){
      if( curdir == NULL){
	fprintf(stderr, "ERROR: curdir not set: call mkdir\n");
      }else{
	myfs_ls_sortname(curdir);
      }
    }else if (0 == strcmp(tok, "rm")){
      if( curdir == NULL){
	fprintf(stderr, "ERROR: curdir not set: call mkir\n");
      }else{
	while( (arg = strtok(NULL, " ")) != NULL){
	  myfs_rm(curdir, arg);
	}
      }
    }else if (0 == strcmp(tok, "touch")){
      if( curdir == NULL){
	fprintf(stderr, "ERROR: curdir not set: call mkir\n");
      }else{
	while( (arg = strtok(NULL, " ")) != NULL){
	  myfs_touch(curdir, arg);
	}
      }
    }else{ //didn't match any command, report an error and some helpful ino
      fprintf(stderr, "ERROR: Unkown command `%s'\n",tok);
      fprintf(stderr, "Available Commands: mkdir, rmdir, ls, touch, rm, lsname, lstime\n");
    }
    
    //free the line so not have memory leaks!
    free(line);
  }
}
