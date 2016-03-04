/*************************************************************************
    > File Name: 287.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年03月03日 星期四 11时55分37秒
 ************************************************************************/

#include <stdio.h>

int findDuplicate(int* nums, int numsSize) {
    int slow, fast;

    if (numsSize < 2) return -1;

    slow = nums[0];
    fast = nums[slow];

    while (slow != fast) {
        slow = nums[slow];
        fast = nums[nums[fast]];
    }
    fast = 0;
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
}

int main()
{
    return 0;
}
