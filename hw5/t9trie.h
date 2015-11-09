// Conner Thomas
// CSE 274 Homework 5
// 2-20-15

#ifndef T9TRIE_H_   /* Include guard */
#define T9TRIE_H_

struct str_node;

struct t9_trie_node;

char* word2t9 ( char * word );

void add_word ( char * key, char * nword, struct t9_trie_node * root );

struct t9_trie_node * t9_node_create ( char * nword );

struct str_node * str_node_create ( char * nword );

void free_t9_node ( struct t9_trie_node * node );

#endif // T9TRIE_H_
