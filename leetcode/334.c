/*************************************************************************
    > File Name: 334.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年04月24日 星期日 16时58分59秒
 ************************************************************************/

#include <stdio.h>
#include <limits.h>

#define bool int
#define true 1
#define false 0

bool increasingTriplet(int* nums, int numsSize) {
    int a, b, i;

    a = INT_MAX;
    b = INT_MAX;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] <= a) {
            a = nums[i];
        } else if (nums[i] <= b) {
            b = nums[i];
        } else {
            return true;
        }
    }
    return false;
}

int main()
{
    return 0;
}
