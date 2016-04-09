/*************************************************************************
    > File Name: 154.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 二  4/ 5 23:36:30 2016
 ************************************************************************/

#include <stdio.h>

int findMin(int* nums, int numsSize) {
    int l, r, mid;

    l = 0;
    r = numsSize - 1;

    while(l < r) {
        mid = (l + r) / 2;
        if (nums[mid] < nums[r]) {
            r = mid;
        } else if (nums[mid] > nums[r]) {
            l = mid + 1;
        } else {
            r--;
        }
    }
    return nums[r];
}

int main() {
    int nums[] = {4,5,6,7,0,1,2};
    findMin(nums, 7);
    return 0;
}
