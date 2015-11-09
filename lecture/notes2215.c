// Conner Thomas
// CSE 374 Notes
// 2-2-15

#define MAX_STR 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * reverse(char * s){
 char * result = NULL;
 int L, R;
 char ch;
 
 result = (char*) malloc(strlen(s)+1);
 
 strcpy(result, s);

 L = 0;
 R = strlen(result);

 while (L < R){
  ch = result[L];
  result[L] = result[R];
  result[R] = ch;
  L++; R++;
 }

 return result;
}

int main() {
 char line[MAX_STR];
 char * rev_line;

 printf("Please enter a string: ");
 fgets(line, MAX_STR, stdin);

 printf("The original string was: >%s>\n", line);
 printf("The reversed string is: >%s<\n", rev_line);
 return 0;
}
