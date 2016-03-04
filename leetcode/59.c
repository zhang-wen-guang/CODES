#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays.
 * Note: The returned array must be malloced, assume caller calls free().
 */
/* dir >:0, v:1, <:2, ^:3 */
int** generateMatrix(int n) {
    int **res;
    int dir = 0, i, j, k;
    int lw = 0, uw = 0, rw = 0, dw = 0;

    res = (int **)malloc(sizeof(int *) * n);
    for (i = 0; i < n; ++i) res[i] = (int *)malloc(sizeof(int) * n);
    i = 0; j = 0; k = 1;
    while (1) {
        if (j == n - rw) break;
        while (j < n - rw) res[i][j++] = k++;
        j--;
        k--;
        uw++;
        if (n - dw == i) break;
        while (i < n - dw) res[i++][j] = k++;
        i--;
        k--;
        rw++;
        if (j < lw) break;
        while (j >= lw) res[i][j--] = k++;
        j++;
        k--;
        dw++;
        if (i < uw) break;
        while (i >= uw) res[i--][j] = k++;
        i++;
        k--;
        lw++;
    }
    return res;
}

int main()
{
    int n;
    int **res;
    int i, j;
    while (scanf("%d", &n)) {
        res = generateMatrix(n);
        for (i = 0; i < n; ++i) {
            for (j = 0;j < n; ++j) {
                printf("%d\t", res[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
