#include <stdio.h>
#include <ctype.h>

int lengthOfLastWord(char* s) {
    int i, flag = 0, cnt = 0;
    for (i = 0; s[i] != '\0'; ++i) {
        if (isalpha(s[i])) {
            if (0 == flag) {
                flag = 1;
                cnt = 0;
            }
            cnt++;
        } else {
            if (1 == flag) flag = 0;
        }
    }
    return cnt;
}

int main()
{
    char s[] = "Hello world";
    printf("%d\n", lengthOfLastWord(s));
    return 0;
}
