#include <stdio.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int minDepth(struct TreeNode* root) {
    int depth = 0;
    int flag = 0;
    int size1 = 0;
    int size2 = 0;
    struct TreeNode* a[100];
    struct TreeNode* b[100];

    if (NULL == root) return 0;
    depth++;
    a[size1++] = root;
    while (1) {
        if (0 == flag) {
            size2 = 0;
            for (int i = 0; i < size1; ++i) {
                if (NULL == a[i]->left && NULL == a[i]->right) return depth;
                if (NULL != a[i]->left) b[size2++] = a[i]->left;
                if (NULL != a[i]->right) b[size2++] = a[i]->right;
            }
            depth++;
            flag = 1;
        }
        if (1 == flag) {
            size1 = 0;
            for (int i = 0; i < size2; ++i) {
                if (NULL == b[i]->left && NULL == b[i]->right) return depth;
                if (NULL != b[i]->left) a[size1++] = b[i]->left;
                if (NULL != b[i]->right) a[size1++] = b[i]->right;
            }
            depth++;
            flag = 0;
        }
    }
}

int main()
{
    return 0;
}
