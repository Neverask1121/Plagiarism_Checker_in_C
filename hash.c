#include "hash.h"

unsigned int hash(char *word){
    unsigned int h = 0;
    for(int i=0; word[i]; i++)
        h = (h*31 + word[i]) % TABLE_SIZE;
    return h;
}

void insertHash(Node *table[], char *word){
    unsigned int idx = hash(word);
    Node *temp = table[idx];

    while(temp){
        if(strcmp(temp->word,word)==0){
            temp->count++;
            return;
        }
        temp = temp->next;
    }

    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->count = 1;
    newNode->next = table[idx];
    table[idx] = newNode;
}

int searchHash(Node *table[], char *word){
    unsigned int idx = hash(word);
    Node *temp = table[idx];

    while(temp){
        if(strcmp(temp->word,word)==0)
            return 1;
        temp = temp->next;
    }
    return 0;
}

void clearTable(Node *table[]){
    for(int i=0;i<TABLE_SIZE;i++){
        Node *temp = table[i];
        while(temp){
            Node *del = temp;
            temp = temp->next;
            free(del);
        }
        table[i] = NULL;
    }
}
