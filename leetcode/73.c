/*************************************************************************
    > File Name: 73.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年04月13日 星期三 19时28分27秒
 ************************************************************************/

#include <stdio.h>

void setZeroes(int** matrix, int matrixRowSize, int matrixColSize) {
    int i, j;
    int l = 1, u = 1;

    for (i = 0; i < matrixRowSize; ++i) {
        if (matrix[i][0] == 0) l = 0;
    }
    for (j = 0; j < matrixColSize; ++j) {
        if (matrix[0][j] == 0) u = 0;
    }
    for (i = 1; i < matrixRowSize; ++i) {
        for (j = 1; j < matrixColSize; ++j) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }
    for (i = 1; i < matrixRowSize; ++i) {
        if (matrix[i][0] == 0) {
            for (j = 1; j < matrixColSize; ++j) {
                matrix[i][j] = 0;
            }
        }
    }
    for (j = 1; j < matrixColSize; ++j) {
        if (matrix[0][j] == 0) {
            for (i = 1; i < matrixRowSize; ++i) {
                matrix[i][j] = 0;
            }
        }
    }
    if (0 == l) {
        for (i = 0; i < matrixRowSize; ++i) {
            matrix[i][0] = 0;
        }
    }
    if (0 == u) {
        for (j = 0; j < matrixColSize; ++j) {
            matrix[0][j] = 0;
        }
    }
}

int main()
{
    return 0;
}
