#include <stdio.h>

int main() {
    int num1 = 5;
    int num2 = 10;

    int result = 0;

    result = num1;
    result += num2;

    printf("Result = %d\n", result);

    int i = 0;
    while(i < 5) {
        printf("%d ", i);
        i++;
    }

    return 0;
}