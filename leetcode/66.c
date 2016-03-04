#include <stdio.h>

int* plusOne(int* digits, int digitsSize, int* returnSize) {
    for (int i = digitsSize - 1; i >= 0; --i) {
        digits[i] += 1;
        if (digits[i] < 10) break;
        if (0 != i) {
            digits[i] -= 10;
        } else {
            for (int j = digitsSize; j > 1; --j) {
                digits[j] = digits[j - 1];
                printf("Bingo\n");
            }
            digits[1] = 0;
            digits[0] = 1;
            digitsSize++;
        }
    }
    *returnSize = digitsSize;
    return digits;
}

int main()
{
    int size;
    int a[2];
    a[0] = 9;
    plusOne(a, 1, &size);

    for (int i = 0; i < size; ++i) {
        printf("%d", a[i]);
    }
    printf("\n");
    return 0;
}
