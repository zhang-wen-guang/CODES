/*************************************************************************
    > File Name: 345.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年04月24日 星期日 13时12分45秒
 ************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isVowel(char c) {
    c = tolower(c);
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return 1;
    else 
        return 0;
}

char* reverseVowels(char* s) {
    int l = 0, r;
    char tmp;

    if (NULL == s) return NULL;
    r = strlen(s); 
    printf("strlen = %d\n", r);
    while (l < r) {
        while (!isVowel(s[l]) && l < r) l++;
        while (!isVowel(s[r]) && l < r) r--;
        if (l < r) {
            tmp = s[l];
            s[l++] = s[r];
            s[r--] = tmp;
        }
    }
    return s;
}

int main()
{
    char s[] = "leetcode";
    reverseVowels(s);
    printf("%s\n", s);
    return 0;
}
