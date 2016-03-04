#include <stdio.h>

//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    struct TreeNode* cur = root;

    while ((cur->val - p->val) * (cur->val - q->val) > 0) {
        if (cur->val > p->val)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return cur;
}
int main()
{
    return 0;
}
