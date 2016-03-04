#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* grayCode(int n, int* returnSize) {
    int *res;
    int i, j, k, start, gap;

    *returnSize = 1 << n;
    res = (int *)calloc(*returnSize, sizeof(int));
    for (i = 0; i < n; ++i) {
        start = 1 << i;
        gap = start << 1;
        for (j = start; j < *returnSize; j += 2 * gap) {
            for (k = 0; k < gap; ++k) if (j + k < *returnSize) res[j + k] += start;
        }
    }
    return res;
}

int main()
{
    int n, returnSize;
    int *res, i;

    scanf("%d", &n);
    res = grayCode(n, &returnSize);
    for (i = 0; i < returnSize; ++i) {
        printf("%d\t", res[i]);
    }
    printf("\n");
    return 0;
}
