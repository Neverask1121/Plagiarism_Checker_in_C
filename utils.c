#include "utils.h"
#include "stack.h"

void normalize(char *input, char *output){
    int j=0;
    for(int i=0; input[i]; i++){
        if(isalnum(input[i]) || input[i]==' ')
            output[j++] = tolower(input[i]);
    }
    output[j]='\0';
}

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
