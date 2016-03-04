/*************************************************************************
    > File Name: 318.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: Fri 18 Dec 2015 04:08:22 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxProduct(char** words, int wordsSize) {
    int *bits, i, j, max = 0;

    bits = malloc(wordsSize * sizeof(int));
    for (i = 0; i < wordsSize; ++i) {
        bits[i] = 0;
        for (j = 0; j < strlen(words[i]); ++j) {
            bits[i] = bits[i] | (1 << (words[i][j] - 'a'));
        }
    }
    for (i = 0; i < wordsSize; ++i) {
        for (j = i + 1; j < wordsSize; ++j) {
            if (0 == (bits[i] & bits[j])) {
                if (strlen(words[i]) * strlen(words[j]) > max)
                    max = strlen(words[i]) * strlen(words[j]);
            }
        }
    }
    return max;
}

int main()
{
    int i, j;
    char **words;

    words = (char **)malloc(5 * sizeof(char *));
    words[0] = (char *)malloc(20 * sizeof(char));
    words[1] = (char *)malloc(20 * sizeof(char));
    words[2] = (char *)malloc(20 * sizeof(char));
    words[3] = (char *)malloc(20 * sizeof(char));
    words[4] = (char *)malloc(20 * sizeof(char));
    words[5] = (char *)malloc(20 * sizeof(char));
    strcpy(words[0], "abcw");
    strcpy(words[1], "baz");
    strcpy(words[2], "foo");
    strcpy(words[3], "bar");
    strcpy(words[4], "xtfn");
    strcpy(words[5], "abcdef");

    maxProduct(words, 2);
    printf("%d\n", maxProduct(words, 6));
    return 0;
}
