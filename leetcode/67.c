#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
char* addBinary(char* a, char* b) {
    int lenA, lenB, i, minlen, total;
    int len = 0, flag = 0;
    char *res, ctmp;

    lenA = strlen(a);
    lenB = strlen(b);
    res = (char *)malloc(sizeof(char) * (max(lenA, lenB) + 2));
    minlen = min(lenA, lenB);

    for (i = 0; i < minlen; ++i) {
        res[i] = a[lenA - i - 1] + b[lenB - i - 1] - '0' + flag;
        if (res[i] > '1') {
            res[i] -= 2;
            flag = 1;
        } else {
            flag = 0;
        }
    }

    if (lenA > lenB) {
        while (i < lenA) {
            res[i] = a[lenA - i - 1] + flag;
            if (res[i] > '1') {
                res[i] -= 2;
                flag = 1;
            } else {
                flag = 0;
            }
            i++;
        }
    } else if (lenB > lenA) {
        while (i < lenB) {
            res[i] = b[lenB - i - 1] + flag;
            if (res[i] > '1') {
                res[i] -= 2;
                flag = 1;
            } else {
                flag = 0;
            }
            i++;
        }
    }

    if (1 == flag) res[i++] = '1';
    total = i;
    for (i = 0; i < total / 2; ++i) {
        ctmp = res[i];
        res[i] = res[total - i - 1];
        res[total - i - 1] = ctmp;
    }
    res[total] = '\0';
    return res;
}

int main()
{
    char a[] = "1010";
    char b[] = "1001100";
    printf("%s\n", addBinary(a, b));
    return 0;
}
