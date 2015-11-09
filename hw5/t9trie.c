// Conner Thomas
// CSE 274 Homework 5
// 2-20-15

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t9trie.h"  // Include the header

// define the list nodes that each t9 has
struct str_node {
 char * word;
 struct str_node * next;
};

// define the t9 nodes
struct t9_trie_node {
 // int key; // the kay at the current node (maybe make this a str?)
 struct str_node * words; // linked list of words associated with a node
 struct t9_trie_node * children[8]; // pointer to children nodes
};

// this function free's a t9 trie node from memory, but first checks to make sure all its children are freed.
void free_t9_node ( struct t9_trie_node * node ){
 if( node != NULL ){
  for (int i = 0; i < 8; i++ ){
   if( node->children[i] != NULL){
    free_t9_node(node->children[i]);
    node->children[i] = NULL;
   }
  }
  free(node);
 }
}

// adds a word to the trie, using the t9 key value passed in, starting at the pointer to root
void add_word ( char * key, char * nword, struct t9_trie_node * root ){

 struct t9_trie_node * curr = root; // always start at the root

 for( int i = 0; i < strlen(key) - 1; i++ ){
  // printf("current t9 key = %c\n", key[i]);
  if( curr->children[key[i] - 2] == NULL){
   curr->children[key[i] - 2] = t9_node_create(NULL);
   curr = curr->children[key[i] - 2];
  } else {
   curr = curr->children[key[i] - 2];
  }
 }

 if (curr->children[key[strlen(key) - 1] - 2] != NULL){

  // printf("already a node here\n");
  curr = curr->children[key[strlen(key) - 1] - 2];
  struct str_node * currWr = curr->words;

  if (curr->words == NULL ){
   struct str_node * strnode = str_node_create(nword);
   curr->words = strnode;
  } else {

   // printf("word passed: %s\n", currWr->word);
   while (currWr->next != NULL){
    // printf("word passed: %s\n", currWr->word);
    currWr = currWr->next;
   }
   struct str_node * strnode = str_node_create(nword);
   currWr->next = strnode;
   // printf("word added: %s\n", currWr->next->word);

  }
 } else {
  // printf("current t9 key = %c\n", key[strlen(key) - 1]);
  curr->children[key[strlen(key) - 1] - 2] = t9_node_create(nword);
  // printf("word: %s\n", curr->children[key[strlen(key) - 1] - 2]->words->word);
 }
}

// this method creates a node for the t9 trie, and allocates memory for all of the structs within
struct t9_trie_node * t9_node_create( char * nword ) {

 // allocate memory for the struct with 8 pointers
 struct t9_trie_node * new_node = (struct t9_trie_node *) calloc( 8, sizeof(struct t9_trie_node) );

 if( nword == NULL  ){
  new_node->words = NULL;
 } else {
  // printf("making a node with string %s\n", nword);
  struct str_node * new_nodenode = str_node_create(nword);
  new_node->words = new_nodenode;
 }

 for(int i = 0; i < 8; i++){
  new_node->children[i] = NULL;
 }
 return new_node;
}

// creates a string node for the string linked list
struct str_node * str_node_create( char * nword ){

 struct str_node * new_node = (struct str_node *)malloc( sizeof(struct str_node *) );
 char * d = (char *)malloc( sizeof(char)*strlen(nword) );
 strncpy(d, nword, strlen(nword));
 new_node->word = d;
 new_node->next = NULL;

 return new_node;
}

// this method takes in a pointer to a string and returns a pointer to a string
// containing the corrosponding t9 key. It returns a string because it is easier to iterate
//over char by char than an int.
char * word2t9( char * word ){

 char * result = malloc (sizeof (char) * strlen(word));
 // switch statement to decode the word into t9
 for(int i = 0; i < strlen(word); i++){
  switch(word[i]){
   case('a'):
   case('b'):
   case('c'): strcat(result, "2"); break;
   case('d'):
   case('e'):
   case('f'): strcat(result, "3"); break;
   case('g'):
   case('h'):
   case('i'): strcat(result, "4"); break;
   case('j'):
   case('k'):
   case('l'): strcat(result, "5"); break;
   case('m'):
   case('n'):
   case('o'): strcat(result, "6"); break;
   case('p'):
   case('q'):
   case('r'):
   case('s'): strcat(result, "7"); break;
   case('t'):
   case('u'):
   case('v'): strcat(result, "8"); break;
   case('w'):
   case('x'):
   case('y'):
   case('z'): strcat(result, "9"); break;
   default: break;
  }
  // printf("%s\n", result);
 }
 return result;
}
