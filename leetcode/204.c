#include <stdio.h>
#include <stdlib.h>

int countPrimes(int n) {
    int i, j, count;
    char *p;

    p = (char *)malloc(n * sizeof(char));
    for (i = 2; i < n; ++i) p[i] = 't';
    for (i = 2; i * i < n; ++i) {
        if ('t' != p[i]) continue;
        for (j = i * i; j < n; j += i) p[j] = 'f';
    }
    count = 0;
    for (i = 2; i < n; ++i) if ('t' == p[i]) count++;
    return count;
}

int main()
{
    printf("%d\n", countPrimes(7));
    return 0;
}
