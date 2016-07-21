/*************************************************************************
    > File Name: 3.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 二  6/ 7 21:54:31 2016
 ************************************************************************/

#include <stdio.h>

#define max(a, b) (a) > (b) ? (a) : (b);
int lengthOfLongestSubstring(char* s) {
    int left = -1;
    int maxlen = 0;
    int i;
    int dict[256];

    for (i = 0; i < 256; ++i) dict[i] = -1;

    for (i = 0; i < strlen(s); ++i) {
        if (left < dict[s[i]]) left = dict[s[i]];
        dict[s[i]] = i;
        maxlen = max(maxlen, i - left);
    }
    return maxlen;
}

int main()
{
    return 0;
}
