/*************************************************************************
    > File Name: 337.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 六  4/ 2 22:58:58 2016
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

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int max(int a, int b) {
    return a > b ? a : b;
}

int* robSub(struct TreeNode *root) {
    int *res, *lres, *rres;

    res = (int *)malloc(sizeof(int) * 2);
    if (NULL == root) {
        res[0] = 0;
        res[1] = 0;
    } else {
        lres = robSub(root->left);
        rres = robSub(root->right);
        res[0] = root->val + lres[1] + rres[1];
        res[1] = max(lres[0], lres[1]) + max(rres[0], rres[1]);
        free(lres);
        free(rres);
    }
    return res;
}

int rob(struct TreeNode* root) {
    int *res = robSub(root);
    return max(res[0], res[1]);
}

int main()
{
    return 0;
}
