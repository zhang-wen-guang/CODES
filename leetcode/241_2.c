#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* diffWaysToCompute(char* input, int* returnSize) {
    int *res1, *res2, returnSize1, returnSize2, *res;
    int resCount = 0, opCount = 0, mallocSize = 1;
    char op, tmpbuf[200];

    for (int i = 0; input[i] != '\0'; ++i) if (!isdigit(input[i])) opCount++;
    while (opCount) {
        mallocSize *= opCount;
        opCount--;
    }
    res = (int *)malloc(sizeof(int) * mallocSize);
    *returnSize = 0;
    for (int i = 0; input[i] != '\0'; ++i) {
        if ('+' == input[i] || '-' == input[i] || '*' == input[i]) {
            op = input[i];
            strcpy(tmpbuf, input);
            tmpbuf[i] = '\0';
            res1 = diffWaysToCompute(tmpbuf, &returnSize1);
            res2 = diffWaysToCompute(input + i + 1, &returnSize2);
            *returnSize += returnSize1 * returnSize2;
            for (int j = 0; j < returnSize1; ++j) {
                for (int k = 0; k < returnSize2; ++k) {
                    if ('+' == op) {
                        res[resCount++] = res1[j] + res2[k];
                    } else if ('-' == op) {
                        res[resCount++] = res1[j] - res2[k];
                    } else {
                        res[resCount++] = res1[j] * res2[k];
                    }
                }
            }
        }
    }
    if (resCount == 0) {
        res[0] = atoi(input);
        *returnSize = 1;
    }
    return res;
}

int main()
{
    char s[] = "2-1-1";
    int *res, size;
    res = diffWaysToCompute(s, &size);
    for (int i = 0; i < size; ++i) {
        printf("i = %d : %d\n", i, res[i]);
    }
    return 0;
}
