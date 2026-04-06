#include "compare.h"
#include "common.h"
#include "hash.h"
#include "utils.h"

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
