#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

/* USAGE Information */
char USAGE[] = "flines [OPTIONS] [file]\n"
  "\n"
  "Will print the specified bytes to stdout..\n"
  "\n"
  "OPTIONS:\n"
  "  -s start_offset \t Specify the start offset\n"
  "  -e end_offset   \t Specify the end offset\n"
  "\n"
  "EXAMPLES:\n"
  "flines -s 10 -e 20 file : print between the bytes between offset 10 and 20\n"
  "flines -s 20 -e 10 file : ERROR: end offset can be greater than start offset\n"
  "flines -s 10 file : print bytes between offset 10 and the end of the file\n"
  "flines -e 10 file : print bytes from start of file until 10 from end\n"
  "flines file : print all bytes of file, like cat\n"
  "flines -e -10 : ERROR: cannot have negative offsets\n";


//OPTIONS
typedef struct{
  int start; //the start offset
  int end; //the end offset
  int f_index; //ignore
} opt_t;

//parsing commmand line options : DO NOT EDIT
void parse_args(int argc, char * argv[], opt_t * opts){
  int c;

  opts->start=-1;
  opts->end=-1;
  
  while((c = getopt(argc,argv, "hs:e:")) != -1){
      switch(c)
	{
	case 'h':
	  printf("%s", USAGE);
	  exit(0);
	  break;
	case 's':
	  if(sscanf(optarg,"%d",&(opts->start)) == 0){
	    fprintf(stderr, "ERROR: Invlaid value for start_offset");
	    fprintf(stderr, "USAGE");
	    exit(1);
	  }
	  break;
	case 'e':
	  if(sscanf(optarg,"%d",&(opts->end)) == 0){
	    fprintf(stderr, "ERROR: Invlaid value for end_offset");
	    fprintf(stderr, "USAGE");
	    exit(1);
	  }
	  break;
	default:
	  fprintf(stderr, "ERROR: Unknown option '%c' \n", c);
	  exit(0);
	  break;
	}
    }
  
  opts->f_index = optind;
}

int main(int argc, char * argv[]){
  
  opt_t opts;
  int i;
  FILE * file;
  char c;

  parse_args(argc,argv,&opts);

  if(opts.f_index == argc){
    fprintf(stderr, "ERROR: Require a file argument\n");
    exit(1);
  }else{

    if( (file = fopen(argv[opts.f_index], "r"))  == NULL){
      fprintf(stderr, "ERROR: Invalid file\n");
      exit(1);
    }
  }


  //TODO: Complete the program
  //
  //    YOU MUST USE fseek()! and apropriate reading and writing procedures
  //
  //    command line options are stored in the opts structure
 int eof;

  i= 0;
  if((opts.start < -1) || (opts.end < -1)){
    fprintf(stderr, "ERROR: can't have negaitatve ofsets cheater\n");
   
  }
  if(fseek(file, opts.end * -1, SEEK_END) < fseek(file, opts.start, SEEK_SET)){
    fprintf(stderr, "ERROR:Invalid start and end (end < start)\n");

  }
  else if ((opts.start == -1) && (opts.end == -1)){
    eof = fseek(file, 0, SEEK_END) + ftell(file);
    fseek(file, 0, SEEK_SET);
    while(i < eof){
      c = fgetc(file);
      write(1, &c, 1);
      i++;
    }
  }
  else if((opts.start > -1) && (opts.end == -1)){
    eof = fseek(file, -1, SEEK_END) + ftell(file);
    i = fseek(file, opts.start, SEEK_SET) + ftell(file);
    while(i < eof){
      c = fgetc(file);
      write(1, &c, 1);
      i++;
    }
    
  }
  else if((opts.start == -1) && (opts.end >= -1)){
    eof = fseek(file, -1, SEEK_END) + ftell(file);
    i = fseek(file, -1 * opts.end , SEEK_END) + ftell(file);
    while(i < eof){
      c = fgetc(file);
      write(1, &c, 1);
      i++;
    }
  }
  else{
    eof = fseek(file, -1 * opts.end -1, SEEK_END) + ftell(file);
    i = fseek(file, opts.start, SEEK_SET) + ftell(file);
    while(i < eof){
      c = fgetc(file);
      write(1, &c, 1);
      i++;
    }
  }
  close(file);
  return 0;
}
