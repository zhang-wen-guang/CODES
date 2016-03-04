#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int digits(int n) {
    int count = 0;

    if (0 == n) return 1;
    while (n) {
        n /= 10;
        count++;
    }
    return count;
}

char** summaryRanges(int* nums, int numsSize, int* returnSize) {
    int flag = 0, i, j, count = 1, head = 0, tail, order = 0;
    char **res;

    if (0 == numsSize) return NULL;
    if (1 == numsSize) {
        res = malloc(sizeof(char *));
        res[0] = malloc(10 * sizeof(char));
        sprintf(res[0], "%d", nums[0]);
        *returnSize = 1;
        return res;
    }

    for (i = 0; i < numsSize - 1; ++i) if (nums[i] + 1 != nums[i + 1]) count++;

    res = malloc(count * sizeof(char *));
    *returnSize = count;

    for (i = 1; i < numsSize; ++i) {
        if (nums[i - 1] + 1 < nums[i]) {
            res[order] = malloc((30) * sizeof(char));
            if (i - head > 1) {
                sprintf(res[order], "%d->%d", nums[head], nums[i - 1]);
            } else {
                sprintf(res[order], "%d", nums[head]);
            }
            order++;
            head = i;
        }
    }
    res[order] = malloc((30) * sizeof(char));
    if (numsSize - head > 1) {
        sprintf(res[order], "%d->%d", nums[head], nums[i - 1]);
    } else {
        sprintf(res[order], "%d", nums[head]);
    }
    return res;
}

int main()
{
    int size;
    char **res;
    char buf[20];
    int test[] = {-2147483648,-2147483647,2147483647};
    res = summaryRanges(test, 3, &size);
    for (int i = 0; i < 2; ++i) {
        printf("%s\n", res[i]);
    }
    return 0;
}
