#include <stdio.h>
#include <stdlib.h>

int* getRow(int rowIndex, int* returnSize) {
    int *ret;
    int numerator = 1;
    int denominator = 1;

    *returnSize = rowIndex + 1;
    ret = (int *)malloc((rowIndex + 1) * sizeof(int));

    for (int i = 0; i <= rowIndex; ++i) ret[i] = 1;

    if (1 == rowIndex) return ret;

    ret[0] = 1;
    ret[1] = 2;
    ret[2] = 1;

    for (int i = 3; i <= rowIndex; ++i) {
        for (int j = i - 1; j > 0; --j) {
            ret[j] = ret[j - 1] + ret[j];
        }
    }
    return ret;
}

int main()
{
    int a;
    int *p;

    p = getRow(12, &a);
    for (int i = 0; i <= 12; ++i) {
        printf("%d\t", p[i]);
    }
    printf("\n");
    return 0;
}
