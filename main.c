#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*****************************************************/
/*     FLIL - Forth-like Interpreted Language        */
/*             By: aslikr42069                       */
/*****************************************************/

#define PLUS_SYMBOL      43  /* + */
#define MINUS_SYMBOL     45  /* - */
#define MULT_SYMBOL      42  /* * */
#define DIV_SYMBOL       47  /* / */
#define AND_SYMBOL       38  /* & */
#define XOR_SYMBOL       94  /* ^ */
#define OR_SYMBOL        124 /* | */
#define MOD_SYMBOL       37  /* % */
#define STORE_SYMBOL     33  /* ! */

#define TABLE_SIZE       1250
#define INIT_STACK_SIZE  32

typedef struct TOKENSTR{
 uint16_t length;
 size_t start;
}TOKENSTR;

typedef struct SYMBOL_TABLE_T{
 uint8_t  type; /* 0 = empty, 1 = var, 2 = function*/
 size_t start;
 uint16_t length;
 uint32_t address;
}SYMBOL_TABLE_T;

uint32_t hash(char *string, size_t start, uint16_t length){
 uint32_t intermediate = 1;
 for(size_t i = start; i < (start + length); i++){
  intermediate *= (uint32_t) string[i];
 }
 return intermediate % TABLE_SIZE;
}

void tokenize(const char *input, TOKENSTR *tokens, uint32_t *count){
 size_t i = 0;
 size_t startingIndex = 0;
 size_t endingIndex;
 uint32_t tokenCount = 0;
 while(input[i] != '\0'){
  while(input[i] != ' ' && input[i] != '\0' && input[i] != '\n' && input[i] != '\t'){
   i++;
  }
  endingIndex = i-1;
  i++;
  if(input[endingIndex] == ' ' || input[endingIndex] == '\n' || input[endingIndex] == '\t'){
   startingIndex = i;
   continue;
  }
  tokenCount++;
  tokens = (TOKENSTR *) reallocarray(tokens, tokenCount, sizeof(TOKENSTR));
  tokens[tokenCount - 1].length = endingIndex - startingIndex + 1;
  tokens[tokenCount - 1].start = startingIndex;
  startingIndex = i;
  if(input[i-1] == '\0'){
   break;
  }
 }
 *count = tokenCount;
}

void parse(TOKENSTR *tokens, uint32_t count, SYMBOL_TABLE_T *symbol_table, uint32_t *stack){
 for(uint32_t i = 0; i < count; i++){
  printf("Token number %d parsed\n", i);
 }
}

int main(){
 char *test = "100 15 +";
 TOKENSTR *toks;
 uint32_t stack[32];
 uint32_t count = 0;
 SYMBOL_TABLE_T symbol_table[1250];
 toks = (TOKENSTR *) calloc(1, sizeof(TOKENSTR));
 tokenize(test, toks, &count);
 parse(toks, count, symbol_table, stack);
 /*for(uint32_t i = 0; i < count; i++){
  for(uint32_t j = toks[i].start; j < (toks[i].start + toks[i].length); j++){
   printf("%c", test[j]);
  }
  printf("\n");
  printf("hash: %d\n", hash(test, toks[i].start, toks[i].length));
 }*/
 return 0;
}
