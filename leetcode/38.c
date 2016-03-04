#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* countAndSay(int n) {
    char *s, b[100000], *p1, *p2, *tmp;
    char a[100000] = "1";
    int i, j, last = 0, p = 0;

    s = (char *)malloc(100000 * sizeof(char));

    p1 = a;
    p2 = b;
    for (i = 2; i <= n; ++i) {
        last = 0;
        p = 0;
        for (j = 0; p1[last] != '\0'; ++j) {
            if (p1[j] != p1[last]) {
                sprintf(p2 + p, "%d%d", j - last, p1[j - 1] - '0');
                last = j;
                p = strlen(p2);
            }
        }
        tmp = p1;
        p1 = p2;
        p2 = tmp;
    }
    for (i = 0; i <= strlen(p1); ++i) s[i] = p1[i];
    return s;
}

int main()
{
    char *s = NULL;

        //countAndSay(i);
    printf("%s\n", countAndSay(50));
    return 0;
}
