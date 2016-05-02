#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]){
  
  uid_t my_uid = 35001;
  struct passwd * pwd;

  pwd = getpwuid(35001);
  
  printf("My username is: %s\n", pwd->pw_name);

  return 0;
}
