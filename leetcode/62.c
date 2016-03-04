#include <stdio.h>

int uniquePaths(int m, int n) {
    if (1 == m || 1 == n) return 1;
    return uniquePaths(m - 1, n) + uniquePaths(m , n - 1);
}

int main()
{
    printf("%d\n", uniquePaths(2, 7));
    return 0;
}
