#include <stdio.h>

int maxProfit(int* prices, int pricesSize) {
    int sum = 0;
    for (int i = 0; i < pricesSize - 1; ++i) {
        if (prices[i] < prices[i + 1]) sum += (prices[i + 1] - prices[i]);
    }
    return sum;
}

int main()
{
    int a[] = {3,2,6,5,0,3};
    printf("%d\n", maxProfit(a, 6));
    return 0;
}
