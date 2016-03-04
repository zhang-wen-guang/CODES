#include <stdio.h>

int missingNumber(int* nums, int numsSize) {
    int sum = 0;

    if (NULL == nums || 0 == numsSize) return 0;
    for (int i = 0; i < numsSize; ++i) sum += nums[i];
    return (1 + numsSize) * numsSize / 2 - sum;
}

int main()
{
    int nums[] = {0, 3, 1};
    printf("%d\n", missingNumber(nums, 3));
    return 0;
}
