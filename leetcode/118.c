#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int** generate(int numRows, int** columnSizes, int* returnSize) {
    if (0 == numRows) return 0;

    int i, j;
    int **result;
    int *size;

    result = (int **)malloc(sizeof(int *) * numRows);
    size = (int *)malloc(sizeof(int) * numRows);

    for (i = 0; i < numRows; ++i) {
        size[i] = i + 1;
    }

    for (i = 0; i < numRows; ++i) {
        result[i] = (int *)malloc(sizeof(int) * (i + 1));
        for (j = 0; j < i + 1; ++j) {
            if (0 == j || i == j) {
                result[i][j] = 1;
                continue;
            }
            if (i > 1) {
                result[i][j] = result[i - 1][j - 1] + result[i - 1][j];
            }
        }
    }
    *columnSizes = size;
    *returnSize = numRows;
    return result;
}

int main()
{
    int **a, **b;
    int *returnSize;
    a = generate(10, b, returnSize);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < i + 1; ++j) {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
