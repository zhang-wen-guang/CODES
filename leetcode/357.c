/*************************************************************************
    > File Name: 357.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: Thu 07 Jul 2016 07:55:45 PM CST
 ************************************************************************/

#include <stdio.h>

int countNumbersWithUniqueDigits(int n) {
    if (n > 10) return 0;
    int ans[11] = {0, 10, 91, 739, 5275, 32491, 168571,
    712891, 2345851, 5611771, 8877691};
    return ans[n];
}


int main()
{
    int i;
    int sum = 0;
    int f[] = {10, 81, 648, 4536, 27216, 136080, 544320, 1632960, 3265920, 3265920};
    for (i = 0; i < 10; ++i) {
        sum += f[i];
        printf("%d\n", sum);
    }
    return 0;
}
