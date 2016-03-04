#include <stdio.h>
#include <limits.h>

#define bool int
#define true 1
#define false 0

bool isUgly(int num) {
    if (num <= 0) return false;
    while (0 == num % 2) num /= 2;
    while (0 == num % 3) num /= 3;
    while (0 == num % 5) num /= 5;
    if (1 == num) return true;
    return false;
}

int main()
{
    for (int i = 1; i < 200; ++i) {
        if (isUgly(i)) printf("%d\n", i);
    }
    return 0;
}
