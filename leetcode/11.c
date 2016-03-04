/*************************************************************************
    > File Name: 11.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: Fri Dec  4 16:42:34 2015
 ************************************************************************/

#include <stdio.h>

int maxArea(int* height, int heightSize) {
    int left = 0, right = heightSize - 1;
    int leftH, rightH, low;
    int max = 0, tmp;

    while (left < right) {
        leftH = height[left];
        rightH = height[right];
        low = leftH < rightH ? leftH : rightH;
        tmp = low * (right - left);
        max = tmp > max ? tmp : max;
        while (height[left] <= low) left++;
        while (height[right] <= low) right--;
    }
    return max;
}

int main()
{
    return 0;
}
