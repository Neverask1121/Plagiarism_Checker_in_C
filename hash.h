#ifndef HASH_H
#define HASH_H

#include "common.h"

typedef struct Node{
    char word[WORD_LEN];
    int count;
    struct Node *next;
} Node;

unsigned int hash(char *word);
void insertHash(Node *table[], char *word);
int searchHash(Node *table[], char *word);
void clearTable(Node *table[]);

#endif
