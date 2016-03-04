#include <stdio.h>

#define max(a, b) a > b ? a : b
int maxProfit(int* prices, int pricesSize) {
    int buy;
    int premax = 0;

    buy = prices[0];
    for (int i = 0; i < pricesSize; ++i) {
        if (prices[i] < buy) buy = prices[i];
        premax = max(premax, prices[i] - buy);
    }
    return premax;
}

int main()
{
    int a[] = {2, 1, 2, 0, 1};
    printf("%d\n", maxProfit(a, 5));
    return 0;
}
