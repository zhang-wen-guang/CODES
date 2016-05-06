/*************************************************************************
    > File Name: 313.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年04月13日 星期三 10时13分39秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int nthSuperUglyNumber(int n, int* primes, int primesSize) {
    int *res, *index;
    int i, j;

    res = (int *)malloc(n * sizeof(int));
    index = (int *)malloc(primesSize * sizeof(int));
    res[0] = 1;
    for (i = 0; i < primesSize; ++i) index[i] = 0;
    for (i = 1; i < n; ++i) res[i] = INT_MAX;

    for (i = 1; i < n; ++i) {
        for (j = 0; j < primesSize; ++j) {
            if (primes[j] * res[index[j]] < res[i]) {
                res[i] = primes[j] * res[index[j]];
            }
        }
        for (j = 0; j < primesSize; ++j) {
            if (res[i] == primes[j] * res[index[j]])
                index[j]++;
        }
    }
#if 0
    for (i = 0; i < n; ++i) {
        printf("%d\t", res[i]);
    }
    printf("\n");
#endif
    return res[n - 1];
}

int main()
{
    int primes[] = {2, 3, 5};
    int ans;

    ans = nthSuperUglyNumber(10, primes, 3);
    printf("%d\n", ans);
    return 0;
}
