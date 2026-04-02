#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 1000
#define WORD_LEN 50
#define MAX_LINE 512
#define THRESHOLD 0.5

/* ---------------- STACK ---------------- */

typedef struct {
    char data[WORD_LEN];
    int top;
} Stack;

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

/* ---------------- HASH + LINKED LIST ---------------- */

typedef struct Node{
    char word[WORD_LEN];
    int count;
    struct Node *next;
}Node;

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

/* ---------------- NORMALIZATION ---------------- */

void normalize(char *input, char *output){
    int j=0;
    for(int i=0; input[i]; i++){
        if(isalnum(input[i]) || input[i]==' ')
            output[j++] = tolower(input[i]);
    }
    output[j]='\0';
}

/* ---------------- PROCESS LINE ---------------- */

void processLine(char *line, Node *table[]){

    Stack s;
    initStack(&s);

    char word[WORD_LEN];

    for(int i=0;;i++){

        if(isalnum(line[i])){
            push(&s, line[i]);
        }
        else{
            if(s.top!=-1){

                stackToWord(&s, word);

                insertHash(table, word);

                clearStack(&s);
            }

            if(line[i]=='\0') break;
        }
    }
}

/* ---------------- JACCARD ---------------- */

float jaccard(Node *t1[], Node *t2[]){

    int intersection=0, unionCount=0;

    for(int i=0;i<TABLE_SIZE;i++){
        Node *temp = t1[i];

        while(temp){
            if(searchHash(t2, temp->word))
                intersection++;
            unionCount++;
            temp = temp->next;
        }
    }

    for(int i=0;i<TABLE_SIZE;i++){
        Node *temp = t2[i];

        while(temp){
            if(!searchHash(t1, temp->word))
                unionCount++;
            temp = temp->next;
        }
    }

    if(unionCount==0) return 0;
    return (float)intersection/unionCount;
}

/* ---------------- CLEAR TABLE ---------------- */

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

/* ---------------- COMPARE FILES ---------------- */

void compareFiles(char *file1, char *file2){

    FILE *f1 = fopen(file1,"r");
    FILE *f2 = fopen(file2,"r");

    if(!f1 || !f2){
        printf("Error opening files\n");
        return;
    }

    char line1[MAX_LINE], line2[MAX_LINE];
    int matched=0, total=0;

    while(fgets(line1,sizeof(line1),f1) &&
          fgets(line2,sizeof(line2),f2)){

        Node *t1[TABLE_SIZE]={NULL};
        Node *t2[TABLE_SIZE]={NULL};

        char norm1[MAX_LINE], norm2[MAX_LINE];

        normalize(line1, norm1);
        normalize(line2, norm2);

        processLine(norm1, t1);
        processLine(norm2, t2);

        float sim = jaccard(t1,t2);

        if(sim >= THRESHOLD)
            matched++;

        total++;

        clearTable(t1);
        clearTable(t2);
    }

    fclose(f1);
    fclose(f2);

    float percent = (total==0)?0:(float)matched/total*100;

    printf("\nComparing with %s\n", file2);
    printf("Matching Lines: %d/%d\n", matched, total);
    printf("Similarity: %.2f%%\n", percent);
}

/* ---------------- MAIN ---------------- */

int main(int argc, char *argv[]){

    if(argc<3){
        printf("Usage: %s base file1 file2 ...\n", argv[0]);
        return 0;
    }

    for(int i=2;i<argc;i++){
        compareFiles(argv[1], argv[i]);
    }

    return 0;
}