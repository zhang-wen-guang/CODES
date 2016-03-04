#include <stdio.h>
#define bool int
#define true 1
#define false 0

bool canWinNim(int n) {
    if (0 != n % 4) return true;
    return false;
}

int main()
{
    int n;

    while (EOF != scanf("%d", &n)) {
        if (true == canWinNim(n)) printf("can win\n");
        else printf("can not win\n");
    }
    return 0;
}
