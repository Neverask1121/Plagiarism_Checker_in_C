#include <stdio.h>

int main() {
    int x = 5;
    int y = 10;

    int sum = x + y;
    int diff = x - y;

    printf("Sum = %d\n", sum);
    printf("Difference = %d\n", diff);

    for(int i=0;i<5;i++){
        printf("%d ", i);
    }

    return 0;
}