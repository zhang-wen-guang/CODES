/*************************************************************************
    > File Name: 300.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 一  4/ 4 22:00:08 2016
 ************************************************************************/

#include <stdio.h>

#define max(x, y) ((x) > (y) ? (x) : (y))

int lengthOfLIS(int* nums, int numsSize) {
    int i, j, maxlen;
    int *tmp = (int *)malloc(sizeof(int) * numsSize);

    for (i = 0; i < numsSize; ++i) tmp[i] = 1;
    for (i = 1; i < numsSize; ++i) {
        for (j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                tmp[i] = max(tmp[j] + 1, tmp[i]);
            }
        }
    }
    maxlen = tmp[0];
    for (i = 0; i < numsSize; ++i)
        if (maxlen < tmp[i]) maxlen = tmp[i];
    return maxlen;
}

int main() {
    return 0;
}
