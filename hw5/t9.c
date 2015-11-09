// Conner Thomas
// CSE 274 Homework 5
// 2-20-15
// This program emulates the t9 typing style of flip-phones
// It reads a string of numbers from the command line and outputs
// the corrosponding word that would appear as dictated by t9

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t9trie.h"

// #define TRIE_LEN 8  // don't actually use this because t9 is always 8 buttons

// define the list nodes that each t9 has
struct str_node {
 char * word;
 struct str_node * next;
};

// define the t9 nodes
struct t9_trie_node {
 struct str_node * words; // linked list of words associated with a node
 struct t9_trie_node * children[8]; // pointer to children nodes
};

int main( int argc, char *argv[] ){

 // at least two arguments are required - check for them
 if(argc < 2){
  fprintf(stderr, "Usage: %s DICTFILE\n", argv[0]);
  return(-1);
 }

 FILE *dictf; // pointer to the file struct
 char wordin[100]; // for each word we read in
 dictf = fopen(argv[1], "r"); // the dict file in argv[1]
 char * rootstr = NULL;
 struct t9_trie_node * root = t9_node_create(rootstr); // create the root of the tree

 // printf("%s\n",root->words->word);

 while(fgets(wordin, 100, dictf)){
  // printf("%s - ", wordin);
  if(wordin[strlen(wordin) - 1] == '\n'){
   wordin[strlen(wordin) - 1] = 0;
  }
  char * wordt9 = word2t9(wordin);  // convert word to t9 numbers - DONE
  // printf("word: %s  key: %s\n", wordin, wordt9);
  add_word( wordt9, wordin, root );  // add word to trie, making new node if neededn - DONE
 }

 char * inputcode = calloc( 100, sizeof(char) );
 struct t9_trie_node * curr = root;
 struct str_node * strlst;
 //char * currword;

 printf("Enter \"exit\" to quit.  \n");

 while (1){

  printf("Enter Key Sequence (or \"#\" for next word):\n");
 	printf("> ");  // prompt for a code
  scanf("%s", inputcode);

  // if the user says to exit, exit
  if ( strcmp(inputcode, "exit") == 0 ){
   break;

  } else if ( inputcode[0] == 35 ){ // else if the user inputs "#" cycle the words

   if (strlst->next == NULL){
    printf("\tThere are no more T9onyms\n");
   } else {
    strlst = strlst->next;
    printf("\t\'%s\'\n", strlst->word);
   }

  } else { // Otherwise start over and look for the code
   // TODO: make sure were not getting NULL back for anything

   for( int i = 0; i < strlen(inputcode); i++ ){
    if (curr->children[inputcode[i] - 2] == NULL){break;}
    curr = curr->children[inputcode[i] - 2];
   }
   if ( curr->words != NULL ){
    strlst = curr->words;
    printf("\t\'%s\'\n", strlst->word);
   } else {
    printf("\tNot found in current dictionary.\n");
   }
  }
  curr = root;
 }
 free_t9_node(root);
 return 0;
}
