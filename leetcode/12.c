#include <stdio.h>
#include <stdlib.h>

char k[3][4] = {"M", "MM", "MMM"};
char b[9][5] = {"C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
char s[9][5] = {"X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
char g[9][5] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

char* intToRoman(int num) {
    int gw, sw, bw, qw;
    int size = 0;
    char res[20];
    int i;
    char *buf;

    gw = num % 10;
    sw = (num / 10) % 10;
    bw = (num / 100) % 10;
    qw = (num / 1000) % 10;

    i = 0;
    if (0 != qw) {
        while ('\0' != k[qw - 1][i]) {
            res[size++] = k[qw - 1][i++];
        }
    }

    i = 0;
    if (0 != bw) {
        while ('\0' != b[bw - 1][i]) {
            res[size++] = b[bw - 1][i++];
        }
    }
    printf("Bingo\n");

    i = 0;
    if (0 != sw) {
        while ('\0' != s[sw - 1][i]) {
            res[size++] = s[sw - 1][i++];
        }
    }

    i = 0;
    if (0 != gw) {
        while ('\0' != g[gw - 1][i]) {
            res[size++] = g[gw - 1][i++];
        }
    }

    buf = (char *)malloc(sizeof(char) * (size + 1));
    for (i = 0; i < size; ++i) {
        buf[i] = res[i];
    }
    buf[size] = '\0';
    return buf;
}

int main()
{
    char *s;
    s = intToRoman(1984);
    printf("%s\n", s);
    return 0;
}
