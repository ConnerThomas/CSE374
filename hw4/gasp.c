// Conner Thomas
// CSE 374 Homework 4
// 2-2-15
// GASP is a linux command line utility similar to grep. It takes in
// a string and file names as arguments and searches for matches of
// that string in the specified files.

#define MAX_LEN 501
#define WORD_LEN 101

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int n_flag = 0; // 1 if '-n' option is present, 0 if not
int i_flag = 0; // 1 if '-i' option is present, 0 if not

void toLower(char *, char *);

void findMatches(char **, int, char*);

int main(int argc, char *argv[]){
 
 int optind; // int to iterate through options
 char word[WORD_LEN]; // array to copy the string in args into 
 int word_loc;

 // at least three arguments are required - check for them
 if(argc < 3){
  fprintf(stderr, "Usage: %s [OPTIONS] STRING FILE (FILE...)\n", argv[0]);
  return(-1);
 }
 
 // parses the command line options with a switch statement and updates global flags
 for(optind = 1; optind < argc && argv[optind][0] == '-'; optind++){
  switch (argv[optind][1]) {
   case 'i': i_flag = 1; break;
   case 'n': n_flag = 1; break;
  }
 } 
 word_loc = i_flag + n_flag + 1;
// strncpy(word,argv[word_loc], sizeof(argv[word_loc]));
 strcpy(word,argv[word_loc]);
 findMatches(argv, argc, word);
 
 return 0;
}

// toLower takes pointers to strings and makes out the lowercase of in.
void toLower(char *in, char *out){
 for(int j = 0; in[j]; j++){ // convert word to lowercase
  out[j] = tolower(in[j]);
 }
}

// findMatches takes in a string and matches it against the file 
// or files passed in as arguments. argv is a pointer to the main
// argv args, and argc is the number of arguments. word is the string to search for.
void findMatches(char *argv[], int argc, char word[]){

 FILE *fp; // pointer to the file struct
 char linein[MAX_LEN]; // allocated array to hold each line we read form the file
 char linelower[MAX_LEN]; // if we ignore case we ned a new place to put the converted string
 int linenum; // keeps track of the line number, in case the -n option is used
 int start_arg; // easy access to the index of the first file to search
 
 start_arg = i_flag + n_flag + 2; // trick to get the arg # of the file
         
 if(i_flag){
  toLower(word, word); // destructively make word all lowercase
 }

 for(int i = start_arg; i < argc; i++){ // iterate over file in args
  fp = fopen(argv[i], "r"); // open file
  linenum = 1; //start line num over for each file
  if(fp==NULL){ // make sure the file exists and was opened correctly
   fprintf(stderr, "gasp: cannot open %s\n", argv[i]);
   return;
  }  
  while(fgets(linein, MAX_LEN, fp)){
   if(i_flag){
    strncpy(linelower, linein, sizeof(linein)); // copy the line in so we can make it lowercase
    toLower(linein, linelower); // make the copiedline lowercase
    if(strstr(linelower, word) != NULL){ // search for one string inside the other
     if(n_flag){ // add line number if -n option
      printf("%s %d:%s", argv[i], linenum, linein);
     }else{
      printf("%s %s", argv[i], linein);
     }
    }
   }else{
    if(strstr(linein, word) != NULL){
     if(n_flag){ // add line number if -n option
      printf("%s %d:%s", argv[i], linenum, linein);
     }else{
      printf("%s %s", argv[i], linein);
     }
    }
   }
   linenum++;
  }
  fclose(fp);
 }
}
