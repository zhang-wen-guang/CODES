#include <stdio.h>

bool isIsomorphic(char* s, char* t) {
    int i;
    char tranS[256] = {0};
    char tranT[256] = {0};

    for (i = 0; s[i] != '\0'; ++i) {
        tranS[s[i]] = t[i];
        tranT[t[i]] = s[i];
    }
    for (i = 0; s[i] != '\0'; ++i) if (transS[s[i]] != t[i] || transT[t[i]] != s[i]) return false;
    return true;
}

int main()
{
    char s[] = "egg";
    char t[] = "add";

    isIsomorphic(s, t);
    return 0;
}
