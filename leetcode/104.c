/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode *root) {
    int maxlen;
    int left, right;
    if (root == NULL) return 0;
    left = maxDepth(root->left);
    right = maxDepth(root->right);
    return left > right ? left + 1 : right + 1;
}
