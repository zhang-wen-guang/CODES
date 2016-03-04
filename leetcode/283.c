#include <stdio.h>

void moveZeroes(int* nums, int numsSize) {
    int p = 0, i = 0;

    if (0 == numsSize) return;

    for (i = 0; i < numsSize; ++i) {
        if (0 != nums[i]) {
            nums[p] = nums[i];
            p++;
        }
    }
    for (i = p; i < numsSize; ++i) nums[i] = 0;
}

int main()
{
    int nums[] = {0, 0, 0, 1, 3, 0, 3, 0, 0, 3, 9 , 0, 0, 2, 0, 0, 0};
    int numsSize = 17;
    int i;

    moveZeroes(nums, 17);
    for (i = 0; i < 17; ++i) {
        printf("%d\n", nums[i]);
    }
    return 0;
}
