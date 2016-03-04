#include <stdio.h>

void sortColors(int* nums, int numsSize) {
    int zero, two;
    int tmp;

    zero = 0;
    two = numsSize - 1;
    for (int i = 0; i < numsSize; ++i) {
        while (2 == nums[i] && i < two) {
            nums[i] = nums[two];
            nums[two--] = 2;
        }
        while (0 == nums[i] && i > zero) {
            nums[i] = nums[zero];
            nums[zero++] = 0;
        }
    }
}

int main()
{
    int a[] = {1, 2, 0, 1, 2, 0, 1, 1, 0, 2, 0, 1, 2};
    sortColors(a, 13);
    for (int i = 0; i < 13; ++i) {
        printf("%d\t", a[i]);
    }
    printf("\n");
    return 0;
}
