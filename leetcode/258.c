#include <stdio.h>

int addDigits(int num) {
    if (0 == num % 9) return 9;
    return num % 9;
}

int main()
{
    for (int i = 0; i < 200; ++i) {
        printf("%d : %d\n", i, addDigits(i));
    }
    return 0;
}
