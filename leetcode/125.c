#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

bool isPalindrome(char* s) {
    int i, cnt = 0;
    char *tmp;

    if (NULL == s) return false;
    for (i = 0; s[i] != '\0'; ++i)
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9'))
            cnt++;

    tmp = (char *)malloc((cnt + 1) * sizeof(char));

    cnt = 0;
    for (i = 0; s[i] != '\0'; ++i) {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9')) tmp[cnt++] = s[i];
        if (s[i] >= 'A' && s[i] <= 'Z') tmp[cnt++] = s[i] + 'a' - 'A';
    }
    for (i = 0; i <= cnt / 2; ++i) {
        if (tmp[i] != tmp[cnt - 1 - i]) return false;
    }
    return true;
}

int main()
{
    char s[] = "A man, a plan, a canal: Panama";
    isPalindrome(s);
    return 0;
}
