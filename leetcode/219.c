#include <stdio.h>

#define bool int
#define true 1
#define false 0

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    for (int i = 0; i < numsSize; ++i) {
        for (int j = 0; j < k && i + j < numsSize; ++j) {
            if (nums[i] == nums[i + j]) return true;
        }
    }
    return false;
}

int main()
{
    return 0;
}
