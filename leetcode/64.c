#include <stdio.h>
#include <stdlib.h>

int minPathSum(int** grid, int gridRowSize, int gridColSize) {
    int i, j, min;
    int *tmp;

    tmp  = (int *)malloc(gridRowSize * sizeof(int));
    tmp[0] = grid[0][0];
    for (i = 1; i < gridRowSize; ++i) tmp[i] = tmp[i - 1] + grid[i][0];
    for (j = 1; j < gridColSize; ++j) {
        tmp[0] += grid[0][j];
        for (i = 1; i < gridRowSize; i++) {
            min = (tmp[i - 1] < tmp[i] ? tmp[i - 1] : tmp[i]);
            tmp[i] = min + grid[i][j];
        }
    }
    return tmp[gridRowSize - 1];
}

int main()
{
    return 0;
}
