#include <sys/types.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]){
  
  uid_t my_gid = 10120;
  struct group * grp;

  grp = getgrgid(my_gid);
  
  printf("My groupname is: %s\n", grp->gr_name);

  return 0;
}
