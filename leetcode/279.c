/*************************************************************************
    > File Name: 279.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 六  4/30 20:38:29 2016
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define min(a, b) ((a) > (b) ? (b) : (a))

int numSquares(int n) {
    int i, j;
    int *dp = (int *)malloc(sizeof(int) * (n + 1));

    if (n <= 0) return 0;
    for (i = 0; i <= n; ++i) dp[i] = INT_MAX;
    dp[0] = 0;

    for (i = 1; i <= n; ++i) {
        for (j = 1; j * j <= i; ++j) {
            dp[i] = min(dp[i], dp[i - j * j] + 1);
        }
    }
    for (i = 1; i <= n; ++i) {
        printf("dp[%d] = %d\n", i, dp[i]);
    }
    return dp[n];
}

int main()
{
    numSquares(120);
    return 0;
}
