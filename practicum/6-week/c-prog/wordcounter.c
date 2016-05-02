#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/***********************************************************
 *
 * Instructions:
 *   - Complete the program below where the TODO's are
 *   - Your program must not segfault or memory errors
 *
 **********************************************************/

//////////////////////////////////////////////////////////////////////////////
// DO *NOT* EDIT BELOW

#define INIT_SIZE 10


typedef struct{

  char * str; //pointer to a string
  int len;    //length of the string

} word_t;

typedef struct{

  word_t ** list; //array of word_t pointer
  int size;       //size of the array
  int nwords;     //number of words in the array

} wordlist_t;

//Load a list of strings from the 
wordlist_t * loadlist(FILE * input){
  char str[1024];
  int i;
  wordlist_t * wordlist;
  word_t ** tmp;
  //allocate wordlist struct
  wordlist = (wordlist_t *) calloc(1, sizeof(wordlist_t));
  
  //initialize wordlist
  wordlist->list   = (word_t **) calloc(INIT_SIZE, sizeof(word_t *));
  wordlist->size   = INIT_SIZE;
  wordlist->nwords = 0;


  i=0;
  while(fscanf(input, "%s", str) != EOF){

    //expand if neccesary
    if( wordlist->size == wordlist->nwords){
      tmp = (word_t **) calloc(wordlist->size * 2, sizeof(word_t *)); //new array
      memcpy(tmp, wordlist->list, wordlist->size * sizeof(word_t *)); //copy old array
      free(wordlist->list); //free old array
      wordlist->list = tmp; //assigne new to told
      wordlist->size *= 2; //update size
    }

    //allocate new node and set values
    wordlist->list[i] = (word_t *) calloc(1, sizeof(word_t));
    wordlist->list[i]->str = strndup(str, 1024); //string duplication, up to 1024 bytes
    wordlist->list[i]->len = strnlen(str, 1024); //string length, up to 1024 bytes
    
    //update the number of words
    wordlist->nwords += 1;

    //increment index
    i++;
  }
  
  //return nodelist
  return wordlist;
}

///////////////////////////////////////////////////////////////////////////////////////////
// *DO* EDIT BELOW

//Print a node list, be sure to match the format!
void printlist(wordlist_t * wordlist){
  //TODO: Complete this function
  // Use this format print for output:
  // printf("%d: %s %d\n", i, wordlist->list[i]->str, wordlist->list[i]->len);
	int ii = 0; 
	for ( ii = 0; ii < wordlist->nwords; ii ++){
		printf("%d: %s %d\n", ii, wordlist->list[ii]->str, wordlist->list[ii]->len);
	
	}

  
}

//Delete a node list by free'ing all allocated memory
void deletelist(wordlist_t * wordlist){
  //TODO: Complete this function
  //Be sure to deallocate ALL allocated memory
	int ii = 0; 
	for ( ii = 0; ii < wordlist->nwords; ii ++){
		free(wordlist->list[ii]->str);
		free(wordlist->list[ii]);
	
	}
	free(wordlist->list);
	free(wordlist);


}

//////////////////////////////////////////////////////////////////////////////
// DO *NOT* EDIT BELOW


int main(int argc, char * argv[]){
  int i;
  wordlist_t * wordlist;
  FILE * input;

  //for each argument
  for(i=1;i<argc;i++){

    //open the file
    if( (input = fopen(argv[i], "r")) != NULL){

      //load a wordlist
      wordlist = loadlist(input);
      
      //print the wordlist
      printf("---- %s ----\n", argv[i]);
      printlist(wordlist);
      printf("\n");
      
      //delte the wordlist
      deletelist(wordlist);

      //close the file
      fclose(input);
    }else{
      //print an erro if can't open the file
      fprintf(stderr, "ERROR: cannot open '%s'\n", argv[i]);
    }

  }
}
