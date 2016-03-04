#include <stdio.h>

// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

int firstBadVersion(int n) {
    int left = 1, right = n, mid;

    while (1) {
        mid = left + (right - left) / 2;

        if (isBadVersion(mid))
            if (!isBadVersion(mid - 1))
                return mid;
            else
                right = mid - 1;
        else
            if (isBadVersion(mid + 1))
                return mid + 1;
            else
                left = mid + 1;
    }
}

int main()
{
    return 0;
}
