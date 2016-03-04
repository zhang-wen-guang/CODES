#include <stdio.h>

#define bool int
#define true 1
#define false 0

bool isPowerOfTwo(int n) {
    int i, size, sum = 0;

    if (n < 0) return false;
    size = sizeof(int) * 8 - 1;
    for (i = 0; i < size; ++i) {
        if((1 << i) & n) sum++;
    }
    if (1 == sum) 
        return true;
    else
        return false;
}
int main()
{
    isPowerOfTwo(31);
    return 0;
}
