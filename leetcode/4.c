/*************************************************************************
    > File Name: 4.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 六  6/25 22:13:25 2016
 ************************************************************************/

#include <stdio.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int m = nums1Size;
    int n = nums2Size;
    int l, r;
    int i, j;

    l = 0;
    r = m - 1;
    while (l < r) {
        i = (l + r) / 2;
        j = (m + n) ...;
        if (nums1[i] < nums1[j + 1] && nums2[j] < nums1[i + 1])
            return () / 2;
        if ()
    }
}

int main()
{
    return 0;
}
