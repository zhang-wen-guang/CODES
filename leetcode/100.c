/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSameTree(struct TreeNode *p, struct TreeNode *q) {
    if (p == NULL && q == NULL) return true;
    if (p == NULL) return false;
    if (q == NULL) return false;
    if (p->val != q->val) return false;
    if (isSameTree(p->left, q->left) && isSameTree(p->right, q->right)) return true;
    return false;
}