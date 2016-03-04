/*************************************************************************
    > File Name: 145.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年03月04日 星期五 13时23分15秒
 ************************************************************************/

#include <stdio.h>

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

int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    struct TreeNode* stack[1024];
    struct TreeNode* cur;
    int top, count;
    int *res;

    if (NULL == root) return NULL;

    res = (int *)malloc(1024 * sizeof(int));
    cur = root->left;
    top = 0;
    count = 0;

    stack[top++] = root;

    while (0 != top) {
        if (NULL == cur) {

        }
    }
}

int main()
{
    return 0;
}
