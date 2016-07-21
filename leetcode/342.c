/*************************************************************************
    > File Name: 342.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年04月24日 星期日 15时33分52秒
 ************************************************************************/

#include <stdio.h>

#define bool int
#define true 1
#define false 0

bool isPowerOfFour(int num) {
    int l = 0, r = 14, mid;
    int midnum;

    if (1 == num) return true;
    while (l <= r) {
        mid = (l + r) / 2;
        midnum = 1 << ((mid + 1) * 2);
        if (num == midnum) {
            return true;
        } else if (num < midnum) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return false;
}

int main()
{
    int i = 1;

    if (isPowerOfFour(1073741825))
        printf("true\n");
    else
        printf("false\n");
    return 0;
}
