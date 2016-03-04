#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

void swap(int * nums, int x,int y)
{
    int temp;
    temp=nums[x];
    nums[x]=nums[y];
    nums[y]=temp;
}
void perm(int* nums,int index, int l, int **result,int * p)
{
    if(index==l)
    {
        for(int i=0;i<=l;i++)
        result[(*p)][i]=nums[i];
        (*p)++;
        return;
    }
    else
    {
        for(int i=index;i<=l;i++)
        {
            swap(nums,index,i);
            perm(nums,index+1,l,result,p);
            swap(nums,i,index);
        }
    }
}
int** permute(int* nums, int numsSize, int* returnSize)
{
    *returnSize=1;
    int i,t,j,k=0;
    int *p =&k;
    for(i=1;i<=numsSize;i++)
    *returnSize=*returnSize*i;
    t=*returnSize;
    int ** result=(int **)malloc(t * sizeof(int *));
    for (i=0; i<t; i++)
    {
         result[i] = (int *)malloc(numsSize * sizeof(int));
         for(j=0;j<numsSize;j++)
         result[i][j]=0;
    }
    perm(nums,0,numsSize-1,result,p);
    return result;
}

int main()
{
    int i, j, nums[] = {1, 2, 3};
    int **res, returnSize;

    res = permute(nums, 3, &returnSize);

    for (i = 0; i < returnSize; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%d\t", res[i][j]);
        }
        printf("\n");
    }

    return 0;
}
