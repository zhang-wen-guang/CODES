/*************************************************************************
    > File Name: 74.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: Tue 22 Dec 2015 09:56:06 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    int big, small, mid;
    int tarline;


    big = matrixRowSize - 1;
    small = 0;
    while (big >= small) {
        mid = (big + small) / 2;
        if (matrix[mid][0] == target) return true;

        if (matrix[mid][0] > target)
            big = mid - 1;
        else
            small = mid + 1;
    }
    tarline = big;
    small = 0;
    big = matrixColSize - 1;
    while (big >= small) {
        mid = (big + small) / 2;
        if (matrix[tarline][mid] == target) return true;
        if (matrix[tarline][mid] > target)
            big = mid - 1;
        else
            small = mid + 1;
    }
    return false;
}

int main()
{
    int i, j;
    int tar;
    int **matrix;
    int tmp[3][4] = {{1,   3,  5,  7},
          {10, 11, 16, 20},
            {23, 30, 34, 50}};

    matrix = (int **)malloc(3 * sizeof(int *));
    for (i = 0; i < 3; ++i)
        matrix[i] = (int *)malloc(4 * sizeof(int));

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 4; ++j) {
            matrix[i][j] = tmp[i][j];
        }
    }


    tar = searchMatrix(matrix, 3, 4, 30);
    printf("tar = %d\n", tar);
    return 0;
}
