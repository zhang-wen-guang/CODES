/*************************************************************************
    > File Name: 216.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年03月07日 星期一 20时19分25秒
 ************************************************************************/

#include <stdio.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int** combinationSum3(int k, int n, int** columnSizes, int* returnSize) {
    int **res;
    int count = 0;
    int *arr;
    int min_n, max_n;

    if (k > 9) return NULL;
    min_n = (1 + k) * k / 2;
    max_n = (19 - k) * k / 2;
    if (n < min_n) return NULL;
    if (n > max_n) return NULL;

    arr = (int *)malloc(sizeof(int) * k);
    res = (int **)malloc(sizeof(int *) * 1024);
    *columnSizes = (int *)malloc(sizeof(int*) * 1024);

    for (int i = 0; i < k; ++i) arr[i] = i + 1;
    arr[k - 1] = n - (k * (k - 1) / 2);
    for (int i = k - 1; i > 0; --i) {
        if (arr[i] > i - k + 10) arr[i - 1] += arr[k] - (i - k + 10);
    }
    if (arr[k - 1] > 9) {
        arr[k - 2] = arr[k - 1] - 9;
        arr[k - 1] = 9;
    }
}

int main() {
    return 0;
}
