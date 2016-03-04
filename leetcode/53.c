#include <stdio.h>

#define max(a, b) (a > b ? a : b)
int maxSubArray(int* nums, int numsSize) {
    int sum, ans;

    sum = 0;
    ans = nums[0];
    for (int i = 0; i < numsSize; ++i) {
        sum += nums[i];
        ans = max(sum, ans);
        sum = max(sum, 0);
    }
    return ans;
}
int main()
{
    int a = 4;
    int b = 3;
    printf("%d\n", max(a, b));
    return 0;
}
