/*************************************************************************
    > File Name: 344.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 六  4/23 16:46:16 2016
 ************************************************************************/

#include <stdio.h>

char* reverseString(char* s) {
    int l = 0, r = 0;
    char tmp;

    if (NULL == s) return NULL;
    while ('\0' != s[r]) r++;
    while (l < r) {
        tmp = s[l];
        s[l] = s[r];
        s[r] = tmp;
    }
    return s;
}

int main()
{
    return 0;
}
