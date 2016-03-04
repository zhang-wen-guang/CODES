#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int l = 1, r = 1;
    int *res;

    *returnSize = numsSize;
    res = (int *)malloc(sizeof(int) * numsSize);
    for (int i = 0; i < numsSize; ++i) res[i] = 1;

    for (int i = 1; i < numsSize; ++i) {
        l *= nums[i - 1];
        r *= nums[numsSize - i];
        res[i] *= l;
        res[numsSize - i - 1] *= r;
    }
    return res;
}

int main()
{
    int size, *res;
    int t[] = {1,2,3,4};

    res = productExceptSelf(t, 4, &size);
    for (int i = 0; i < size; ++i) {
        printf("%d\n", res[i]);
    }
    return 0;
}
