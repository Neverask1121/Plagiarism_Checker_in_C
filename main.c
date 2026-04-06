#include "common.h"
#include "compare.h"

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