#include <stdio.h>
#include <string.h>

#define bool int
#define true 1
#define false 0

bool isValid(char* s) {
    int i, top = 0;
    char tmp[1024];

    for (i = 0; i < strlen(s); ++i) {
        switch (s[i]) {
            case '{':
            case '(':
            case '[':
                tmp[top++] = s[i];
                break;
            case '}':
                if (0 == top) return false;
                if (tmp[top - 1] != '{') return false;
                top--;
                break;
            case ')':
                if (0 == top) return false;
                if (tmp[top - 1] != '(') return false;
                top--;
                break;
            case ']':
                if (0 == top) return false;
                if (tmp[top - 1] != '[') return false;
                top--;
                break;
        }
    }

    if (0 == top)
        return true;
    else
        return false;
}

int main()
{
    char s[] = "([)]";
    if (1 == isValid(s))
        printf("true\n");
    else
        printf("false\n");
    return 0;
}
