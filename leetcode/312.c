/*************************************************************************
    > File Name: 312.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年03月06日 星期日 14时01分45秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int maxCoins(int* nums, int numsSize) {
    int nums2[1024];
    int count = 0;
    int len, left, right, final, tmp;
    int **dp;

    nums2[count++] = 1;
    for (int i = 0; i < numsSize; ++i) {
        if (0 != nums[i]) nums2[count++] = nums[i];
    }
    nums2[count++] = 1;

    /* 定义dp数组 */
    dp = (int **)malloc(sizeof(int *) * count);
    for (int i = 0; i < count; ++i) {
        dp[i] = (int *)malloc(sizeof(int) * count);
    }

    /* 初始化dp数组 */
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < count; ++j) {
            dp[i][j] = 0;
        }
    }

    for (len = 1; len < count - 1; ++len) {
        for (left = 0; left < count - 1 - len; ++left) {
            right = left + len + 1;
            for (final = left + 1; final < right; ++final) {
                printf("left = %d\n", left);
                printf("right = %d\n", right);
                printf("final = %d\n", final);
                if ((tmp = nums2[final] * nums2[left] * nums2[right] + dp[left][final] + dp[final][right]) > dp[left][right])
                    dp[left][right] = tmp;
                printf("tmp = %d\n\n", tmp);
            }
        }
    }
    return dp[0][count - 1];
}

int main()
{
    int nums[4] = {3, 1, 5, 8};
    maxCoins(nums, 4);
    return 0;
}
