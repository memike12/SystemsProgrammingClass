#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <time.h>

#include "filesystem.h"

dir_t * myfs_mkdir(){
  //TODO
  dir_t * files = (dir_t *) calloc(1, sizeof(file_t *));
  files->flist=calloc(5, sizeof(file_t));
  files->size=INIT_SIZE;
  files->nfiles=0;
  return files;
}

void myfs_rmdir(dir_t * dir){
  //TODO
  free(dir);
}

int myfs_rm(dir_t * dir, char *fname){
  //TODO
  int i;
  for(i=0;i<dir->nfiles;i++){
    if (strcmp(dir->flist[i]->fname,fname)==0){
      dir->flist[i]->fname=NULL;
      dir->flist[i]->last=0;
      dir->nfiles--;
      free(dir->flist[i]);
    }
  }
   

  return -1;
}
 
  

void myfs_ls(dir_t * dir){
  int i;
  int top = dir->nfiles;
  //printf("%d", dir->nfiles);
  for(i=0; i<top ; i++){
    if(dir->flist!=NULL){
    char * filename = dir->flist[i]->fname;
    time_t time = dir->flist[i]->last;
    printf("%s", filename);
    printf("         %s", ctime(&time));
    }
    else
    {}
  }
}



file_t * myfs_touch(dir_t * dir, char *fname){
  //TODO
  //int index = dir->nfiles;
  //printf(index);
  int i;
  //printf("%d", dir->size);
  //printf("%d", dir->nfiles);

  if(dir->nfiles>=dir->size){
    dir->flist=(file_t **) realloc(dir->flist, 2*dir->nfiles*sizeof(file_t));
        dir->size=dir->size*2;
      }
  int count;
  for(count=0;count<dir->size;count++){
   if(dir->flist[count]!=NULL){
    if(strcmp(dir->flist[count]->fname,fname)==0){
     dir->flist[count]->last=time(NULL);
     return NULL;
     }
   }}


  for(i=0;i<dir->size;i++){

    if(dir->flist[i]==NULL){
      
      dir->flist[i]=calloc(1, sizeof(file_t));

      dir->flist[i]->fname=strdup(fname);

      dir->flist[i]->last=time(NULL);

      dir->nfiles++;
 
      return dir->flist[i]; 
    }
  }
  return NULL;
}


void myfs_ls_sorttime(dir_t * dir){
  //TODO: Extra Credit

}
void myfs_ls_sortname(dir_t * dir){
  //TODO: Extra Credit
}
