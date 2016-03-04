#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** binaryTreePaths(struct TreeNode* root, int* returnSize) {
    int leftSize = 0, rightSize = 0;
    char **res, **leftRes, **rightRes;

    if (NULL == root) {
        *returnSize = 0;
        return NULL;
    }
    /* leaf node */
    if (NULL == root->left && NULL == root->right) {
        *returnSize = 1;
        res = (char **)malloc(sizeof(char *));
        res[0] = (char *)malloc(20 * sizeof(char));
        sprintf(res[0], "%d", root->val);
        return res;
    }
    if (NULL != root->left) {
        leftRes = binaryTreePaths(root->left, &leftSize);
    }
    if (NULL != root->right) {
        rightRes = binaryTreePaths(root->right, &rightSize);
    }
    *returnSize = leftSize + rightSize;
    res = (char **)malloc(sizeof(char *) * (*returnSize));
    for (int i = 0; i < leftSize; ++i) {
        res[i] = (char *)malloc(1024 * sizeof(char));
        sprintf(res[i], "%d->", root->val);
        strcat(res[i], leftRes[i]);
    }
    for (int i = leftSize; i < *returnSize; ++i) {
        res[i] = (char *)malloc(1024 * sizeof(char));
        sprintf(res[i], "%d->", root->val);
        strcat(res[i], rightRes[i - leftSize]);
    }
    return res;
}

int main()
{
    int size;
    char **s;
    struct TreeNode a, b, c, d;
    a.val = 1;
    b.val = 2;
    c.val = 3;
    d.val = 5;

    a.left = &b;
    a.right = &c;
    b.left = NULL;
    b.right = &d;
    c.left = NULL;
    c.right = NULL;
    d.left = NULL;
    d.right = NULL;
    s = binaryTreePaths(&a, &size);
    for (int i = 0; i < size; ++i) {
        printf("%s\n", s[i]);
    }

    return 0;
}
