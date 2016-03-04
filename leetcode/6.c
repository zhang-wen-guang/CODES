#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* convert(char* s, int numRows) {
    int size, i, j;
    int tmp[100], tmp_size = 0, delta, res_size = 0;
    char *res;

    if (NULL == s) return NULL;
    if (1 == numRows) return s;
    size = strlen(s);
    delta = 2 * numRows - 2;

    res = (char *)malloc(1000 * sizeof(char));
    for (i = 0; i < size; i += delta) {
        tmp[tmp_size++] = i;
        res[res_size++] = s[i];
    }
    for (i = 1; i < numRows; ++i) {
        for (j = 0; j < tmp_size; ++j) {
            if (tmp[j] + i < size) {
                res[res_size++] = s[tmp[j] + i];
            }
            if (tmp[j] + delta - i < size && delta > 2 * i) {
                res[res_size++] = s[tmp[j] + delta - i];
            }
        }
    }
    res[res_size++] = '\0';
    return res;
}

int main()
{
    char s[] = "Apalindromeisaword,phrase,number,orothersequenceofunitsthatcanbereadthesamewayineitherdirection,withgeneralallowancesforadjustmentstopunctuationandworddividers.";;
    printf("%s\n", convert(s, 2));
    return 0;
}
