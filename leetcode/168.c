#include <stdio.h>
#include <stdlib.h>

char* convertToTitle(int n) {
    char tmp[20], *res;
    int i, cnt = 0;
    
    if (0 == n) return NULL;
    while (n) {
        if (0 != n % 26) {
            tmp[cnt++] = 'A' + n % 26 - 1;
        } else {
            tmp[cnt++] = 'Z';
            n--;
        }
        n /= 26;
    }

    res = (char *)malloc((cnt + 1) * sizeof(char));
    res[cnt] = '\0';
    for (i = 0; i < cnt; ++i) res[i] = tmp[cnt - 1 - i];
    return res;
}

int main()
{
    printf("%s\n", convertToTitle(26));
    return 0;
}
