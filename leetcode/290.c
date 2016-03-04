#include <stdio.h>
#include <string.h>

#define bool int
#define true 1
#define false 0

bool wordPattern(char* pattern, char* str) {
    char strs[26][40];
    char *p;
    char tmp[20];
    int no;
    int is_set[26] = {0};
    int pattern_len;
    int word_len, i, j, k;

    p = str;
    pattern_len = strlen(pattern);

    while (isspace(*p)) p++;
    for (i = 0; i < pattern_len; ++i) {
        printf("i = %d\n", i);
        printf("pattern = %c\n", pattern[i]);
        no = pattern[i] - 'a';
        if (0 == is_set[no]) {
            word_len = 0;
            while (*p != '\0' && !isspace(*p)) strs[no][word_len++] = *p++;
            strs[no][word_len] = '\0';
            for (j = 0; j < 26; ++j) {
                if (j != no && 0 == strcmp(strs[j], strs[no])) return false;
            }
            is_set[no] = 1;
            printf("pattern = %c strs[%d] = %s\n", pattern[i], no, strs[no]);
            for (k = 0; k < 26; k++) {
                if (1 == is_set[k]) {
                    printf("strs[%d] = %s\n", k, strs[k]);
                }
            }
        } else {
            word_len = 0;
            while (*p != '\0' && !isspace(*p)) tmp[word_len++] = *p++;
            tmp[word_len] = '\0';
            printf("pattern = %c tmp = %s\n", pattern[i], tmp);
            printf("strs[%d] = %s\n", no, strs[no]);
            if (0 != strcmp(tmp, strs[no])) return false;
            for (k = 0; k < 26; k++) {
                if (1 == is_set[k]) {
                    printf("strs[%d] = %s\n", k, strs[k]);
                }
            }
        }
        while (*p != '\0' && isspace(*p)) p++;
    }
    if (*p != '\0') return false;
    return true;
}

int main()
{
    FILE *fp;
    char pattern[1000];
    char str[5000];

    fp = fopen("data", "r");
    getchar();
    scanf("%s", pattern);
    pattern[strlen(pattern) - 1] = '\0';
    getchar();
    getchar();
    gets(str);
    str[strlen(str) - 1] = '\0';

    printf("%s\n", pattern);
    printf("%s\n", str);

    if (wordPattern(pattern, str) == true) printf("True\n");
    else printf("False\n");
    return 0;
}
