#include <stdio.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int countNode(struct TreeNode *root) {
    if (NULL == root) return 0;
    return countNode(root->left) + countNode(root->right) + 1;
}
int kthSmallest(struct TreeNode* root, int k) {
    int left;
    left = countNode(root->left);
    if (k - 1 == left) return root->val;
    if (k < left) return kthSmallest(root->left, k);
    return kthSmallest(root->right, k - 1 - left);
}

int main()
{
    return 0;
}
