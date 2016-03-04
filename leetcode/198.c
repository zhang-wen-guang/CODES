int rob(int* nums, int numsSize) {
    int a, b, tmp;

    a = nums[0];
    b = 0;

    for (int i = 1; i < numsSize; ++i) {
        tmp = a;
        a = b + nums[i];
        b = (tmp > b ? tmp : b);
    }
    return a > b ? a : b;
}
