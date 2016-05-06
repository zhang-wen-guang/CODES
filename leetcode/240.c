/*************************************************************************
    > File Name: 240.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年04月07日 星期四 09时32分49秒
 ************************************************************************/

#include <stdio.h>

#define bool int
#define true  1
#define false 0

bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    int i, j;

    i = 0;
    j = matrixColSize - 1;

    while (i < matrixRowSize && j >= 0) {
        if (target == matrix[i][j]) {
            return true;
        } else if (target > matrix[i][j]) {
            i++;
        } else {
            j--;
        }
    }
    return false;
}

int main()
{
    return 0;
}
