#include <stdio.h>

void rotate(int* nums, int numsSize, int k) {
    int pre = numsSize - k, i = 0, tmp;

    for (i = 0; i < (pre + 1) / 2; ++i) {
        tmp = nums[i];
        nums[i] = nums[pre - i - 1];
        nums[pre - i - 1] = tmp;
    }
    for (i = pre; i <= (pre + numsSize - 1) / 2; ++i) {
        tmp = nums[i];
        nums[i] = nums[pre + numsSize - 1 - i];
        nums[pre + numsSize - 1 - i] = tmp;
    }
    for (i = 0; i < numsSize / 2; ++i) {
        tmp = nums[i];
        nums[i] = nums[numsSize - 1 - i];
        nums[numsSize - 1 - i] = tmp;
    }
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7};
    rotate(a, 7, 3);
    for (int i = 0; i < 7; ++i) printf("%d\t", a[i]);
    printf("\n");
    return 0;
}
