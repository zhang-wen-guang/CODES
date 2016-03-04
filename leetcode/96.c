#include <stdio.h>

int numTrees(int n) {
    int a[1000];

    a[0] = 1;
    a[1] = 1;

    for (int i = 2; i <= n; ++i) {
        a[i] = 0;
        for (int j = 0; j < i; ++j) {
            a[i] += a[j] * a[i - 1 - j];
        }
    }
    return a[n];
}

int main()
{
    printf("%d\n", numTrees(2));
    return 0;
}
