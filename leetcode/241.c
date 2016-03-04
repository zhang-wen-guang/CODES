#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* diffWaysToCompute(char* input, int* returnSize) {
    int nums[100], tmp = 0, numCount = 0, opCount = 0, i, j, sign = 1;
    int nums2[100], *res, newSize, totalSize = 0, *tmpRes;
    char op[100], numTmp[25];
    char newInput[200] = "";

    for (int i = 0; input[i] != '\0'; ++i) {
        if (isdigit(input[i])) {
            tmp *= 10;
            tmp += input[i] - '0';
        } else {
            if ('-' == input[i] && !isdigit(input[i - 1])) {
                sign = -1;
                continue;
            }
            op[opCount++] = input[i];
            nums[numCount++] = sign * tmp;
            sign = 1;
            tmp = 0;
        }
    }
    nums[numCount++] = sign * tmp;

    if (opCount == 1) {
        res = (int *)malloc(sizeof(int));
        *returnSize = 1;
        if ('+' == op[0]) {
            res[0] = nums[0] + nums[1];
        } else if ('-' == op[0]) {
            res[0] = nums[0] - nums[1];
        } else {
            res[0] = nums[0] * nums[1];
        }
        return res;
    }
    res = (int *)malloc(100 * sizeof(int));
    for (i = 0; i < opCount; ++i) {
        newInput[0] = '\0';
        for (j = 0; j < numCount; ++j) nums2[j] = nums[j];
        if ('+' == op[i]) {
            nums2[i + 1] = nums2[i] + nums2[i + 1];
        } else if ('-' == op[i]) {
            nums2[i + 1] = nums2[i] - nums2[i + 1];
        } else {
            nums2[i + 1] = nums2[i] * nums2[i + 1];
        }
        for (j = 0; j < opCount; ++j) {
            if (i == j) continue;
            sprintf(numTmp, "%d", nums2[j]);
            strcat(newInput, numTmp);
            newInput[strlen(newInput) + 1] = '\0';
            newInput[strlen(newInput)] = op[j];
        }
        sprintf(numTmp, "%d", nums2[j]);
        strcat(newInput, numTmp);
        tmpRes = diffWaysToCompute(newInput, &newSize);
        for (j = 0; j < newSize; ++j) {
            res[totalSize + j] = tmpRes[j];
        }
        totalSize += newSize;
    }
    *returnSize = totalSize;
    return res;
}

int main()
{
    int size, *res;
    res = diffWaysToCompute("2*3-4*5", &size);
    for (int i = 0; i < size; ++i) {
        printf("i = %d : %d\n", i, res[i]);
    }
    return 0;
}
