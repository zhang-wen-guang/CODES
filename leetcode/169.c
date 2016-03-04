#include <stdio.h>

int majorityElement(int* nums, int numsSize) {
    int now;
    int i;
    int count;

    now = nums[0];
    count = 1;
    for (i = 1; i < numsSize; ++i) {
        if (0 == count) {
            now = nums[i];
            count++;
        } else if (now == nums[i]) {
            count++;
        } else {
            count--;
        }
    }
    return now;
}

int main()
{
    int a[10];

    a[0] = 4;
    a[1] = 4;
    a[2] = 2;
    a[3] = 4;
    a[4] = 7;
    a[5] = 4;
    a[6] = 4;
    a[7] = 5;
    a[8] = 9;
    a[9] = 4;
    printf("%d\n", majorityElement(a, 10));
    return 0;
}
