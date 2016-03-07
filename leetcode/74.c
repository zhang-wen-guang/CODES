/*************************************************************************
    > File Name: 74.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: Tue 22 Dec 2015 09:56:06 AM CST
 ************************************************************************/

#include <stdio.h>

bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    int big, small, mid;
    int tarline;

    big = matrixColSize - 1;
    small = 0;
    while (big != small) {
        mid = (big + small) / 2;
        if (matrix[mid][0] == target) return true;

        if (matrix[mid][0] > target)
            big = mid;
        else
            small = mid;
    }
    tarline = small;
    big = matrixRowSize - 1;
    while (big != small) {
        mid = (big + small) / 2;
        if (matrix[tarline][mid] == target) return true;
        if (matrix[tarline][mid] > target)
            big = mid;
        else
            small = mid;
    }
    return false;
}

int main()
{
    return 0;
}
    }
}

int main()
{
    return 0;
}
