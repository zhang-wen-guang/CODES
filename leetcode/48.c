#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void rotate(int** matrix, int matrixRowSize, int matrixColSize) {
    int i, j;

    for (i = 0; i < matrixRowSize / 2; ++i) {
        for (j = 0; j < matrixColSize; ++j) {
            swap(&matrix[i][j], &matrix[matrixRowSize - i - 1][j]);
        }   
    }   
    for (i = 0; i < matrixRowSize; ++i) {
        for (j = 0; j < i; ++j) {
            swap(&matrix[i][j], &matrix[j][i]);
        }
    }
}

int main()
{
    return 0;
}
