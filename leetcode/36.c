#include <stdio.h>


#define bool int
#define true 1
#define false 0

bool isValidSudoku(char **board, int boardRowSize, int boardColSize) {
    int i, j, k;
    int i2, j2;
    int a[9];

    for (i = 0; i < boardRowSize; ++i) {
        for (k = 0; k < 9; k++) a[k] = 0;
        for (j = 0; j < boardColSize; ++j) {
            if (board[i][j] >= '1' && board[i][j] <= '9') a[board[i][j] - '1']++;
        }
        for (k = 0; k < 9; ++k) if (a[k] > 1) return false;
    }

    for (i = 0; i < boardColSize; ++i) {
        for (k = 0; k < 9; k++) a[k] = 0;
        for (j = 0; j < boardRowSize; ++j) {
            if (board[j][i] >= '1' && board[j][i] <= '9') a[board[j][i] - '1']++;
        }
        for (k = 0; k < 9; ++k) if (a[k] > 1) return false;
    }

    for (i = 0; i < boardRowSize; i += 3) {
        for (j = 0; j < boardColSize; j += 3) {
            for (k = 0; k < 9; ++k) a[k] = 0;

            for (i2 = i; i2 < i + 3; ++i2) {
                for (j2 = j; j2 < j + 3; ++j2) {
                    if (board[i2][j2] >= '1' && board[i2][j2] <= '9') a[board[i2][j2] - '1']++;
                }
            }
            for (k = 0; k < 9; ++k) if (a[k] > 1) return false;
        }
    }
    return true;
}

int main()
{
    int i, j;
    //char board[10][10] = {".87654321", "2........", "3........", "4........",
    //   "5........", "6........", "7........", "8........", "9........"};
    //for (i = 0; i < 9; ++i) {
    //    for (j = 0; j < 9; ++j) {
    //        printf("%c ", board[i][j]);
    //    }
    //    printf("\n");
    //}
    if (1 == isValidSudoku(9, 9)) printf("ture\n");
    return 0;
}
