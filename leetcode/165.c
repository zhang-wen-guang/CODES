#include <stdio.h>

int compareVersion(char* version1, char* version2) {
    int v1 = 0, v2 = 0, p1 = 0, p2 = 0;

    while (version1[p1] != '\0' && version2[p2] != '\0') {
        while (version1[p1] != '.' && version1[p1] != '\0') {
            v1 *= 10;
            v1 += version1[p1++] - '0';
        }
        if ('.' == version1[p1]) p1++;
        
        while (version2[p2] != '.' && version2[p2] != '\0') {
            v2 *= 10;
            v2 += version2[p2++] - '0';
        }
        if ('.' == version2[p2]) p2++;
        if (v1 > v2) return 1;
        if (v1 < v2) return -1;
        v1 = 0;
        v2 = 0;
    }
    if ('\0' == version1[p1] && '\0' == version2[p2]) return 0;
    if ('\0' == version1[p1]) {
        while ('\0' != version2[p2]) {
            if ('.' == version2[p2]) p2++;
            v2 *= 10;
            v2 += version2[p2++] - '0';
            if (v2 > v1) return -1;
        }
    }
    if ('\0' == version2[p2]) {
        while ('\0' != version1[p1]) {
            if ('.' == version1[p1]) p1++;
            v1 *= 10;
            v1 += version1[p1++] - '0';
            if (v1 > v2) return 1;
        }
    }
    return 0;
}
//    printf("v1h = %d\n", v1h);
//    printf("v2h = %d\n", v2h);
//
//    printf("v1t = %d\n", v1t);
//    printf("v2t = %d\n", v2t);

int main()
{
    char v1[] = "1.1";
    char v2[] = "1.0";
    compareVersion(v1, v2);
    return 0;
}
