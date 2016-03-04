#include <stdio.h>
#include <stdint.h>

uint32_t reverseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; ++i) {
        result <<= 1;
        result |= n & 1;
        n >>= 1;
    }
    return result;
}

int main()
{
    int a = 43261596;
    printf("%d\n", reverseBits(a));
    return 0;
}
