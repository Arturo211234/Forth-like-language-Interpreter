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

#define TABLE_SIZE       1250
#define STACK_SIZE       32

typedef struct TOKENSTR{
 uint16_t length;
 size_t start;
}TOKENSTR;

typedef struct SYMBOL_TABLE_T{
 uint8_t   isEmpty; /* 0 = empty, 1 = not empty */
 size_t    start;
 uint16_t  length;
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

void push(uint32_t *stack, uint8_t *stackCount, uint32_t number){
 if(*stackCount >= (STACK_SIZE - 1)){
  puts("\nERROR: You have pushed too many elements to the stack.\n");
  printf("The maximum number of elements allowed is %d\n", STACK_SIZE);
  exit(1);
 }
 stack[*stackCount++] = number;
}

uint32_t pop(uint32_t *stack, uint8_t *stackCount){
 return stack[*stackCount--];
}

void parse(TOKENSTR *tokens, uint32_t count, SYMBOL_TABLE_T *symbol_table, uint32_t *stack, uint8_t stack_count, char *string){
 for(uint32_t i = 0; i < count; i++){
  if(isdigit((int) *(string + tokens[i].start))){
   uint32_t intermediate = (uint32_t) strtol(&string[tokens[i].start], NULL, 0); // Add intermediate so compiler stops throwing errors 
   push(stack, &stack_count, intermediate);
  } else if(isalpha((int) *(string + tokens[i].start))){
   // Token is function
   // TODO:
   // - Hash the token string
   // - Do linear probing
   // - ????

  } else {
   // If we reach here, it means that the token is either:
   // an arithmetic operator
   // a control char
   switch(*(string + tokens[i].start)){
    case '+':
      // Do addition and stack popping
      break;
    case '-':
      // Do subtraction and stack popping
      break;
    case '*':
      // Do multiplication and stack popping
      break;
    case '/':
      // Do division and stack popping
      break;
    case '&':
      // Do bitwise AND and stack popping
      break;
    case '^':
      // Do bitwise XOR and stack popping
      break;
    case '|':
      // Do bitwise OR and stack popping
      break;
    default:
      puts("Invalid character detected in code!\n");
      break;
   }
  
  }

 }
}


int main(){
 char *test = "100 15 +";
 TOKENSTR *toks;
 uint32_t stack[STACK_SIZE];
 uint32_t token_count = 0;
 uint8_t stack_count = 0;
 SYMBOL_TABLE_T symbol_table[TABLE_SIZE];
 toks = (TOKENSTR *) calloc(1, sizeof(TOKENSTR));
 tokenize(test, toks, &token_count);
 parse(toks, token_count, symbol_table, stack, stack_count, test);
 return 0;
}
