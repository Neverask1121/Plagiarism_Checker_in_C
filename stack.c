#include "stack.h"

void initStack(Stack *s){ s->top = -1; }

void push(Stack *s, char c){
    if(s->top < WORD_LEN-1)
        s->data[++s->top] = c;
}

void clearStack(Stack *s){ s->top = -1; }

void stackToWord(Stack *s, char *word){
    int i;
    for(i=0;i<=s->top;i++)
        word[i] = s->data[i];
    word[i] = '\0';
}
