#include <stdio.h>

int climbStairs(int n) {

    int num1, num2;
    int tmp;
    int i;

    if (1 == n) return 1;
    if (2 == n) return 2;

    num1 = 1;
    num2 = 2;
    for (i = 3; i <= n; ++i) {
        tmp = num1 + num2;
        num1 = num2;
        num2 = tmp;
    }
    return num2;
}

int main()
{
    int i;
    for (i = 1; i < 10; ++i) {
        printf("No %d %d\n", i, climbStairs(i));
    }
    return 0;
}
