/*************************************************************************
    > File Name: 77.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 六  4/ 9 00:24:36 2016
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

void backtrack(int n, int k, int start, int pos, int *path, int **res, int *count) {
    int i;

    if (pos == k) {
        for (i = 0; i < k; ++i) res[*count][i] = path[i];
        (*count)++;
        return;
    }

    for (i = start; i < n + pos + 2 - k; ++i) {
        path[pos] = i;
        backtrack(n, k, i + 1, pos + 1, path, res, count);
    }
}

int** combine(int n, int k, int** columnSizes, int* returnSize) {
    int **res, *path;
    int i, count = 0;
    double total = 1;

    if (k > n) return NULL;
    if (k == n) {
        res = (int **)malloc(sizeof(int *));
        res[0] = (int *)malloc(sizeof(int) * k);
        for (i = 0; i < k; ++i) res[0][i] = i + 1;
        *returnSize = 1;
        (*columnSizes) = (int *)malloc(sizeof(int));
        (*columnSizes)[0] = k;
        return res;
    }
    for (i = 0; i < k; ++i) total *= ((double)(n - i) / (double)(k - i));

    res = (int **)malloc(sizeof(int *) * ((int)total + 1));
    (*columnSizes) = (int *)malloc(sizeof(int) * (int)total + 1);

    for (i = 0; i <= (int)total; ++i) (*columnSizes)[i] = k;
    for (i = 0; i <= (int)total; ++i) res[i] = (int *)malloc(sizeof(int) * k);

    path = (int *)malloc(sizeof(int) * k);
    backtrack(n, k, 1, 0, path, res, &count);
    *returnSize = count;
    return res;
}

int main()
{
    int i, j;
    int **res, *columnSizes;
    int size;

    res = combine(5, 3, &columnSizes, &size);
    for (i = 0; i < 10; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%d\t", res[i][j]);
        }
        printf("\n");
    }
    return 0;
}
