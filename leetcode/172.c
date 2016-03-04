#include <stdio.h>

int trailingZeroes(int n) {
    int tmp = n;
    int res = 0;

    while (n) {
        tmp = n / 5;
        res += tmp;
        n = n / 5;
    }
    return res;
}

int main()
{
    printf("%d\n", trailingZeroes(1808548329));
    return 0;
}
