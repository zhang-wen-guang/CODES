#include <stdio.h>
#include <limits.h>

int reverse(int x) {
    int tmp, res = 0;

    while (x) {
        tmp = x % 10;
        x /= 10;
        if (res > 214748364 || res < -214748364) return 0;
        res *= 10;
        res += tmp;
    }
    return res;
}

int main()
{
    int i;
    while (EOF != scanf("%d", &i)) {
        printf("%d\n", reverse(i));
    }
    return 0;
}
