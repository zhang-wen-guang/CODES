#include <stdio.h>
#include <string.h>

#define bool int
#define true 1
#define false 0

bool isAnagram(char* s, char* t) {
    int i;
    int a[26];

    for (i = 0; i < 26; ++i) a[i] = 0;
    for (i = 0; i < strlen(s); ++i) {
        a[s[i] - 'a']++;
    }
    for (i = 0; i < strlen(t); ++i) {
        a[t[i] - 'a']--;
    }
    for (i = 0; i < 26; ++i)
        if (0 != a[i])
            return false;
    return true;
}

int main()
{
    char s[] = "rat";
    char t[] = "car";
    if (1 == isAnagram(s, t))
        printf("true\n");
    else 
        printf("false\n");
    return 0;
}
