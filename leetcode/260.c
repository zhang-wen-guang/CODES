#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* singleNumber(int* nums, int numsSize, int* returnSize) {
    int *res, dif;

    *returnSize = 2;
    res = (int *)malloc(sizeof(int) * 2);
    res[0] = 0;
    res[1] = 0;
    for (int i = 0; i < numsSize; ++i) {
        res[0] ^= nums[i];
    }
    dif = res[0] & -res[0];
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] & dif) res[1] ^= nums[i];
    }
    res[0] ^= res[1];
    return res;
}

int main()
{
    return 0;
}
