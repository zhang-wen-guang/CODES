/*************************************************************************
    > File Name: 312.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年03月06日 星期日 14时01分45秒
 ************************************************************************/

#include <stdio.h>

int maxCoins(int* nums, int numsSize) {
    int nums2[1024];
    int count = 0;

    nums2[count++] = 1;
    for (int i = 0; i < numsSize; ++i) {
        if (0 != nums[i]) nums2[count++] = nums[i];
    }
    nums2[count++] = 1;
}

int main()
{
    return 0;
}
