/*************************************************************************
    > File Name: 129.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 六  4/30 21:21:04 2016
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
int recursive(struct TreeNode* node, int cur) {
    if (NULL == node) return 0;

    cur = cur * 10 + node->val;
    if (!node->left && !node->right) return cur;
    return recursive(node->left, cur) + recursive(node->right, cur);
}

int sumNumbers(struct TreeNode* root) {
    return recursive(root, 0);
}

int main()
{
    return 0;
}
