#include <stdio.h>

#define max(a, b) (a >= b ? a : b)
#define min(a, b) (a <= b ? a : b)

int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    if (C < E || G < A || H < B || D < F) return (C - A) * (D - B) + (G - E) * (H - F);
    return (C - A) * (D - B) + (G - E) * (H - F) - (min(D, H) - max(B, F)) * (min(C, G) - max(A, E));
}

int main()
{
    int area;

    area = computeArea(-2, -2, 2, 2, -2, -2, 2, 2);
    printf("%d\n", area);
    return 0;
}
