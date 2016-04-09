/*************************************************************************
    > File Name: 289.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 四  4/ 7 21:16:20 2016
 ************************************************************************/

#include <stdio.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

void gameOfLife(int** board, int boardRowSize, int boardColSize) {
    int i, j, m, n;
    int count;

    for (i = 0; i < boardRowSize; ++i) {
        for (j = 0; j < boardColSize; ++j) {
            count = 0;
            for (m = max(i - 1, 0); m < min(boardRowSize, i + 2); ++m) {
                for (n = max(j - 1, 0); n < min(boardColSize, j + 2); ++n) {
                    count += (board[m][n] & 1);
                }
            }
            count -= board[i][j];
            if (1 == board[i][j]) {
                if (count == 2 || 3 == count)
                    board[i][j] |= 2;
            } else {
                if (3 == count)
                    board[i][j] |= 2;
            }
        }
    }
    for (i = 0; i < boardRowSize; ++i) {
        for (j = 0; j < boardColSize; ++j) {
            board[i][j] >>= 1;
        }
    }
}

int main()
{
    return 0;
}
