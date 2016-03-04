#include <stdio.h>
#include <ctype.h>
#include <limits.h>

int myAtoi(char* str) {
    int sign = 1, res = 0, count = 0;
    int max = INT_MAX / 10;

    if (NULL == str) return 0;
    while (isspace(str[count])) count++;
    if ('-' == str[count]) {
        sign = -1;
        count++;
    } else if ('+' == str[count]) {
        count++;
    }

    while (isdigit(str[count])) {
        if (res > max && sign == -1) return INT_MIN;
        if (res > max && sign == 1) return INT_MAX;
        res *= 10;
        res += (str[count++] - '0');
    }
    if (res < 0 && sign == -1) return INT_MIN;
    if (res < 0 && sign == 1)  return INT_MAX;
    res *= sign;
    return res;
}

int main()
{
    printf("%d\n", myAtoi("2147483648"));
    return 0;
}
