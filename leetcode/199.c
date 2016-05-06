/*************************************************************************
    > File Name: 199.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年04月08日 星期五 15时35分27秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int* rightSideView(struct TreeNode* root, int* returnSize) {
    struct TreeNode *queue[2][1024];
    struct TreeNode **p1, **p2;
    int count1 = 0, count2 = 0;
    int i, flag = 0;
    int *res, retSize = 0;

    if (NULL == root) return NULL;
    res = (int *)malloc(sizeof(int) * 1024);
    p1 = queue[0];
    p2 = queue[1];

    *p1 = root;
    count1++;

    while (0 != count1) {
        for (i = 0; i < count1; ++i) {
            if (i == count1 - 1) {
                res[retSize++] = (*p1)->val;
            }
            if (NULL != (*p1)->left) {
                *p2 = (*p1)->left;
                p2++;
                count2++;
            }
            if (NULL != (*p1)->right) {
                *p2 = (*p1)->right;
                p2++;
                count2++;
            }
        }
        if (0 == count2) {
            *returnSize = retSize;
            return res;
        } else {
            p1 = queue[1 - flag];
            p2 = queue[flag];
            flag = 1 - flag;
            count1 = count2;
            count2 = 0;
        }
    }
}

int main()
{
    int size, *res, i;
    struct TreeNode t1, t2;

    t1.right = &t2;
    t1.left = NULL;
    t2.left = NULL;
    t2.right = NULL;
    t1.val = 1;
    t2.val = 2;

    res = rightSideView(&t1, &size);
    for (i = 0; i < size; ++i) {
        printf("%d\t", res[i]);
    }
    printf("\n");

    return 0;
}
