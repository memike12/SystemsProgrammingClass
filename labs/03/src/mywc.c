/*************************************************************
 * mywc.c
 *
 * NAME: Michael Moore
 * ALPHA: 164488
 *
 *************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>


/* USAGE Information */
char USAGE[] = "mywc [OPTIONS] [file] [...]\n"
  "Print the number lines, words, and bytes of each file or from standard input\n"
  "\n"
  "All count information is written to standard out when no options are provided, and\n"
  "by default data is read from standard input if no file is provided. To read from \n"
  "standard input and a file, indicate standard input using '-'\n"
  "\n"
  "OPTIONS:\n"
  "\t -h \t print USAGE\n"
  "\t -l \t print line count\n"
  "\t -w \t print word count\n"
  "\t -c \t print byte count\n";

/**
 * Data type for mywc options
 **/
struct mywc_opt_t{
  int all; 
  int lines; //== 1 if counting lines
  int words; //== 1 if counting words
  int bytes; //== 1 if countying bytes
  int f_index; //index into argv for start of file arguments
};

/**
 * Data type for mywc results
 **/
struct mywc_res_t{
  int lines; //number of lines
  int words; //number of words
  int bytes; //number of bytes
};

/*Function Delceartions*/
void parse_args(int argc, char * argv[], struct mywc_opt_t * opts);
void print_opts(int argc, char * argv[], struct mywc_opt_t * opts);
void count(FILE * f, struct mywc_res_t * res);
void print_res( );


///////////////////////////////////////////////////////////////////////////////


/**
 * parse_args(int argc, char * argv[], struct mywc_opt_t * opts);
 * returns: index of remaining argv[]  values
 *
 * Set the opts structure with apropriate flags and return
 **/
void parse_args(int argc, char * argv[], struct mywc_opt_t * opts){
  int c;

  /*default settings*/
  opts->all = 1;
  opts->lines = 0;
  opts->bytes = 0;
  opts->words = 0;
  opts->f_index = -1;

  /*parse each flag*/
  while ((c = getopt(argc, argv, "wlch")) != -1){

    switch (c)
      {
      case 'h':
	printf("%s", USAGE);
	exit(0);
	break;
      case 'w':
	opts->all = 0;
	opts->words = 1;
	break;
      case 'l':
	opts->all = 0;
	opts->lines = 1;
	break;
      case 'c':
	opts->all = 0;
	opts->bytes = 1;
	break;
      default:
	fprintf(stderr, "mywc: Unknown option '%c' \n", c);
	exit(0);
	break;
      }
  }

  /*if all is set, set all to 1*/
  if (opts->all){
    opts->lines = 1;
    opts->words = 1;
    opts->bytes = 1;
  }
  
  /*store inde of last arguemnt*/
  opts->f_index = optind;

  return;
}

/**
 * print_opts(int argc, char * argv[], struct mywc_opt_t * opts)
 *
 * Debug function to print the settings for mywc
 **/
void print_opts(int argc, char * argv[], struct mywc_opt_t * opts){
  int i;

  printf("all -> %d\n", opts->all);
  printf("lines -> %d\n", opts->lines);
  printf("words -> %d\n", opts->words);
  printf("bytes -> %d\n", opts->bytes);
  printf("f_index -> %d\n", opts->f_index);

  if(opts->f_index == argc){
    printf("file: - (default)\n");
  }else{
    for(i = opts->f_index; i < argc; i++){
      printf("file: %s\n", argv[i]);
    }
  }
}

/**
 * count(FILE * f, struct mywc_res_t * res)
 *
 * Count the number lines, words, and bytes in the file opned at the
 * file pointer f. Set the results in res.
 *
 **/
void count(FILE * f, struct mywc_res_t * res){
  //TODO: Complete this function

}

/**
 * print_res(                    )
 *
 * Print the output for a results. The order of the output is always
 * prefered lines, words, bytes and then file name, dependent on which
 * options are provided. All results are tab deliminated with a
 * leadding tab. 
 *
 **/
void print_res( ){
  //TODO: Complete the function decleration and code

}

int main( int argc, char *argv[] ){


  /* DEFINE MORE VARIABLES HERE*/
  struct mywc_opt_t opts; //options structure
  struct mywc_res_t res, total; //results struct and total
  int i; //iterator
  char * fname; //filename
  FILE * file; //file pointer


  parse_args(argc, argv, &opts); // parse the options
  print_opts(argc, argv, &opts); // debug print, remove before submission


  //TODO: Complete the main logic

  return 0;
}
