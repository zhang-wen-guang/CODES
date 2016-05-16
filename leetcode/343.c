/*************************************************************************
    > File Name: 343.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 六  4/23 23:34:50 2016
 ************************************************************************/

#include <stdio.h>

int integerBreak(int n) {
    int res = 1;

    if (n < 4) return (n - 1);
    if (4 == n) return 4;
    while (n > 4) {
        res *= 3;
        n -= 3;
    }
    return (res * n);
}

int main()
{
    return 0;
}
