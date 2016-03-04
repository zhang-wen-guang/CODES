#include <stdio.h>
#include <stdlib.h>

struct NumArray {
    int *nums;
    int *curSum;
    int size;
};

/** Initialize your data structure here. */
struct NumArray* NumArrayCreate(int* nums, int numsSize) {
    int i;
    struct NumArray *res;

    res = (struct NumArray *)malloc(sizeof(struct NumArray));
    res->nums = (int *)malloc(sizeof(int) * numsSize);
    res->curSum = (int *)malloc(sizeof(int) * numsSize + 1);
    res->size = numsSize;
    res->nums[0] = nums[0];
    res->curSum[0] = 0;
    for (i = 1; i < numsSize; ++i) {
        res->nums[i] = nums[i];
        res->curSum[i] = res->curSum[i - 1] + nums[i - 1];
    }
    res->curSum[i] = res->curSum[i - 1] + nums[i - 1];
    return res;
}

int sumRange(struct NumArray* numArray, int i, int j) {
    return (numArray->curSum[j + 1] - numArray->curSum[i]);
}

/** Deallocates memory previously allocated for the data structure. */
void NumArrayFree(struct NumArray* numArray) {
    if (numArray) {
        if (numArray->nums) free(numArray->nums);
        free(numArray);
    }
}

// Your NumArray object will be instantiated and called as such:
// struct NumArray* numArray = NumArrayCreate(nums, numsSize);
// sumRange(numArray, 0, 1);
// sumRange(numArray, 1, 2);
// NumArrayFree(numArray);

int main()
{
    int sum, i;
    int a[] = {-2, 0, 3, -5, 2, -1};
    struct NumArray *numArray;
    numArray = NumArrayCreate(a, 6);
    printf("numArray->size = %d\n", numArray->size);
    for (i = 0; i < numArray->size; ++i) {
        printf("%d\n", numArray->nums[i]);
    }

    sum = sumRange(numArray, 0, 1);
    printf("sum1 = %d\n", sum);
    sum = sumRange(numArray, 1, 2);
    printf("sum2 = %d\n", sum);
    NumArrayFree(numArray);
    return 0;
}
