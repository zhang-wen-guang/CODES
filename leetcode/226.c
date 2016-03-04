#include <stdio.h>

//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* invertTree(struct TreeNode* root) {
    struct TreeNode *tmp;

    if (NULL == root) return NULL;
    tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

int main()
{
    return 0;
}
