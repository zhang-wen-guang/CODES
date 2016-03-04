#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int count = 0;

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void permuteRecursive(int *nums, int begin, int **res, int numsSize, int *top) {
    int i;

    if (begin == numsSize) {
        for (i = 0; i < numsSize; ++i) res[*top][i] = nums[i];
        (*top)++;
        return;
    }
    for (i = begin; i < numsSize; ++i) {
        swap(&nums[i], &nums[begin]);
        permuteRecursive(nums, begin + 1, res, numsSize, top);
        swap(&nums[i], &nums[begin]);
    }
}
int** permute(int* nums, int numsSize, int* returnSize) {
    int **res, i = numsSize;
    int top = 0;

    *returnSize = numsSize;
    while (--i) (*returnSize) *= i;
    res = (int **)malloc(sizeof(int *) * (*returnSize));
    for (i = 0; i < (*returnSize); ++i) res[i] = (int *)malloc(sizeof(int) * numsSize);
    permuteRecursive(nums, 0, res, numsSize, &top);
    return res;
}

int main()
{
    int i, j, nums[] = {1, 2, 3};
    int **res, returnSize;

    res = permute(nums, 3, &returnSize);

    for (i = 0; i < returnSize; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%d\t", res[i][j]);
        }
        printf("\n");
    }

    return 0;
}
