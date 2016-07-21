/*************************************************************************
    > File Name: 215.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: Fri 08 Jul 2016 12:35:42 AM CST
 ************************************************************************/

#include <stdio.h>

int partion(int *nums, int size) {
    int i = 0;
    int save = nums[0];
    int boundary = 0;

    for (i = 1; i < size; ++i) {
        if (nums[i] < save) {
            nums[boundary] = nums[i];
            boundary++;
            nums[i] = nums[boundary];
        }
    }
    nums[boundary] = save;
    return boundary;
}

void printArray(int *nums, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        printf("%d\t", nums[i]);
    }
    printf("\n");
}

int findKthLargest(int* nums, int numsSize, int k) {
    int *newNums = nums;
    int newSize = numsSize;
    int newK = k;
    int part;
    int rpart;

    while (1) {
        part = partion(newNums, newSize);
        rpart = newSize - part - 1;
        if (newK == rpart + 1) {
            return newNums[part];
        } else if (rpart >= newK) {
            newNums = newNums + part + 1;
            newSize = rpart;
        } else {
            newSize = part;
            newK = newK - rpart - 1;
        }
    }
}

int main()
{
    int i = 0;
    int ret;
    int nums[1024] = {7, 6, 5, 4, 3, 2, 1};

    ret = findKthLargest(nums, 7, 5);
    printf("ret = %d\n", ret);
    return 0;
}
