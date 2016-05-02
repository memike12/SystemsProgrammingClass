#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "filesystem.h"

void test_simple();

void test_expand();

void test_touch();

int main(int argc, char *argv[]){

  test_simple();

  printf("\n\n\n");
  test_expand();

  printf("\n\n\n");
  test_touch();

  //TODO: ADD MORE TESTS HERE

}


void test_simple(){
  dir_t * dir;

  printf("----TEST SIMPLE----\n");
  dir = myfs_mkdir();
  myfs_touch(dir, "Hello");
  myfs_touch(dir, "Goodbye");
  myfs_touch(dir, "what");
  myfs_ls(dir);

  printf("----\n");
  myfs_rm(dir, "Goodbye");
  myfs_ls(dir);
  printf("----\n");
  myfs_rmdir(dir);

}

void test_expand(){
  int i;
  char fname[20];
  dir_t * dir;

  printf("--- TEST EXPAND---\n");
  dir = myfs_mkdir();  
  for(i=0;i < 30;i++){
    snprintf(fname, 20, "file%0d.txt", i);
    myfs_touch(dir, fname);
  }
  myfs_ls(dir);

  printf("----\n");
  for(i=15;i < 30;i++){
    snprintf(fname, 20, "file%0d.txt", i);
    myfs_rm(dir, fname);
  }
  myfs_ls(dir);

  printf("----\n");
  for(i=0;i < 30;i++){
    snprintf(fname, 20, "new%0d.txt", i);
    myfs_touch(dir, fname);
  }
  myfs_ls(dir);
  myfs_rmdir(dir);

}

void test_touch(){
  dir_t * dir;

  printf("--- TEST TOUCH ---\n");

  dir = myfs_mkdir();
  myfs_touch(dir, "Hello");
  myfs_touch(dir, "Goodbye");
  myfs_ls(dir);

  printf("----\n");
  sleep(2);
  myfs_touch(dir, "Hello");
  myfs_ls(dir);

  printf("----\n");
  myfs_rm(dir, "Hello");
  myfs_touch(dir, "Goodbye");
  myfs_ls(dir);

  printf("----\n");
  myfs_touch(dir, "Hello");
  myfs_ls(dir);

  myfs_rmdir(dir);
}
