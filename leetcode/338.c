/*************************************************************************
    > File Name: 338.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 六  4/ 2 20:59:25 2016
 ************************************************************************/

#include <stdio.h>

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int num, int* returnSize) {
    int *res, i;

    res = (int *)malloc(sizeof(int) * (num + 1));
    res[0] = 0;
    for (i = 0; i <= num; ++i) {
        res[i] = res[i >> 1] + i % 2;
    }
    *returnSize = num + 1;
    return res;
}

int main()
{
    return 0;
}
