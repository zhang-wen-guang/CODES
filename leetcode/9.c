#include <stdio.h>

int isPalindrome(int x) {
    if (x < 0) x = -x;
    int y = 0;
    int tmp;

    printf("x = %d\n", x);
    while (0 != x) {
        y *= 10;
        tmp = x % 10;
        x /= 10;
        y += tmp;
    }

    printf("y = %d\n", y);

    return x == y;
}

int main()
{
    isPalindrome(-2147447412);
    return 0;
}
