/*************************************************************************
    > File Name: 309.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: Thu 03 Dec 2015 02:37:52 PM CST
 ************************************************************************/

#include<stdio.h>

int maxProfit(int* prices, int pricesSize) {
    int i, sum = 0;
    int start = 0, end = 1;
    int tmp1, tmp2;

    if (pricesSize < 2) return 0;

    while (1) {
        while (end < pricesSize && prices[end] < prices[start]) {
            start++;
            end++;
        }
        while (end < pricesSize && prices[end] >= prices[start]) end++;
        if (end == pricesSize) {
            if (prices[end - 1] > prices[start])
                sum += prices[end - 1] - prices[start];
            break;
        }
        if (end + 1 < pricesSize && prices[end + 1] < prices[end]) {
            sum += (prices[end - 1] - prices[start]);
            start = end + 1;
            end = start + 1;
        }
        tmp1 = maxProfit(prices + end, pricesSize - end) + prices[end - 2] - prices[start];
        tmp2 = maxProfit(prices + end + 1, pricesSize - end - 1) + prices[end - 1] - prices[start];
        if (tmp1 > tmp2) {
            return tmp1 + sum;
        } else {
            return tmp2 + sum;
        }
    }
    return sum;
}

int main()
{
    int a[] = {1, 2, 3, 0, 2};
    printf("%d\n", maxProfit(a, 5));
    return 0;
}
