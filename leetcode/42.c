/*************************************************************************
    > File Name: 42.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: Mon Jul 11 08:54:28 2016
 ************************************************************************/

#include <stdio.h>

int trap(int* height, int heightSize) {
    int l = 0, r = heightSize - 1;
    int lmax = 0, rmax = 0;
    int res = 0;

    while (l < r) {
        if (height[l] <= height[r]) {
            if (height[l] >= lmax)
                lmax = height[l];
            else
                res += (lmax - height[l]);
            l++;
        } else {
            if (height[r] >= rmax)
                rmax = height[r];
            else
                res += (rmax - height[r]);
            r--;
        }
    }
    return res;
}

int main()
{
    int height[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    int res;

    res = trap(height, sizeof(height) / 4);
    printf("size = %lu\n", sizeof(height) / 4);
    printf("res = %d\n", res);
    return 0;
}
