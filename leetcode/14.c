#include <stdio.h>
#include <stdlib.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    int i, j, flag;
    char cmp;
    char *res;

    if (NULL == strs) return NULL;
    res = (char *)malloc(100 * sizeof(char));
    for (i = 0; strs[0][i] != '\0'; ++i) {
        cmp = strs[0][i];
        flag = 1;
        for (j = 1; j < strsSize; ++j) {
            if (strs[j][i] != cmp) flag = 0;
        }
        if (1 == flag) {
            res[i] = cmp;
        } else {
            break;
        }
    }
    res[i] = '\0';
    return res;
}

int main()
{
    char strs[][20] = {"hello", "hesdf", "hedsfads"};

    printf("%s\n", longestCommonPrefix(strs, 3));
    return 0;
}
