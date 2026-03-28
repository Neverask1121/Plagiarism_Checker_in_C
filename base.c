#include <stdio.h>

int main() {
    int a = 5;
    int b = 10;

    int sum = a + b;
    int diff = a - b;

    printf("Sum = %d\n", sum);
    printf("Difference = %d\n", diff);

    for(int i = 0; i < 5; i++) {
        printf("%d ", i);
    }

    return 0;
}