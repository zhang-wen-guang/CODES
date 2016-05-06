/*************************************************************************
    > File Name: 199.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 四  4/ 7 22:19:41 2016
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
                //printf("i = %d\n", i);
                //printf("count1 = %d\n", count1);
                res[retSize++] = (*p1)->val;
                //printf("val = %d\n", (*p1)->val);
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
            p1++;
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
    struct TreeNode a, b, c;

    a.val = 1;
    b.val = 2;
    c.val = 3;

    a.left = &b;
    a.right = &c;

    b.left = NULL;
    b.right = NULL;

    c.left = NULL;
    c.right = NULL;

    res = rightSideView(&a, &size);
    for (i = 0; i < size; ++i) {
        printf("%d\n", res[i]);
    }
    return 0;
}
