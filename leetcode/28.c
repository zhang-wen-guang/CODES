#include <stdio.h>
#include <string.h>

int strStr(char* haystack, char* needle) {
    int len1, len2, i, j, flag;

    len1 = strlen(haystack);
    len2 = strlen(needle);

    for (i = 0; i <= len1 - len2; ++i) {
        flag = 1;
        for (j = 0; j < len2; ++j) {
            if (haystack[i + j] != needle[j]) {
                flag = 0;
                break;
            }
        }
        if (1 == flag) return i;
    }
    return -1;
}

int main()
{
    char s1[] = "hello";
    char s2[] = "lx";

    printf("%d\n", strStr(s1, s2));
    return 0;
}
