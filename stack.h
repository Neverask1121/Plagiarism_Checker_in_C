#ifndef STACK_H
#define STACK_H

#include "common.h"

typedef struct {
    char data[WORD_LEN];
    int top;
} Stack;

void initStack(Stack *s);
void push(Stack *s, char c);
void clearStack(Stack *s);
void stackToWord(Stack *s, char *word);

#endif
