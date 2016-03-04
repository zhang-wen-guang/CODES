#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

/* m represents left parent left, n represents right parent left*/
void addParent(char ***res, int *top, char *tmp, int m, int n, int size, int *resSize) {
    if (0 == m && 0 == n) {
        if (*top > *resSize) {
            *res = (char **)realloc(*res, (*resSize) * 2 * sizeof(char *));
            (*resSize) *= 2;
        }
        (*res)[*top] = (char *)malloc(sizeof(char) * 2 * size + 1);
        (*res)[*top][0] = '\0';
        strcpy((*res)[(*top)++], tmp);
        return;
    }
    if (m > 0) {
        char tmp1[100] = "";
        strcpy(tmp1, tmp);
        strcat(tmp1, "(");
        addParent(res, top, tmp1, m - 1, n + 1, size, resSize);
    }
    if (n > 0) {
        char tmp2[100] = "";
        strcpy(tmp2, tmp);
        strcat(tmp2, ")");
        addParent(res, top, tmp2, m, n - 1, size, resSize);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    char **res;
    char tmp[100] = "";
    int i, resSize = 100;

    *returnSize = 0;
    res = (char **)malloc(sizeof(char *) * 100);
    addParent(&res, returnSize, tmp, n, 0, n, &resSize);
    return res;
}

int main()
{
    int i, returnSize, size;
    char **res;

    scanf("%d", &size);
    res = generateParenthesis(size, &returnSize);
    //for (i = 0; i < returnSize; ++i) printf("%s\n", res[i]);
    printf("returnSize = %d\n", returnSize);
    return 0;
}
