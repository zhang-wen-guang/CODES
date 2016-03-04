#include <stdio.h>
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
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    struct TreeNode *stack[1000];
    struct TreeNode *tmp;
    int top = 0;
    int a[1000];
    int num = 0;
    int *ret;

    if (NULL != root) stack[top++] = root;
    while (0 != top) {
        a[num++] = stack[top - 1]->val;
        top--;
        tmp = stack[top];
        if (NULL != tmp->right) stack[top++] = tmp->right;
        if (NULL != tmp->left) stack[top++] = tmp->left;
    }
    ret = (int *)malloc(num * sizeof(int));
    for (int i = 0; i < num; ++i) {
        ret[i] = a[i];
    }
    *returnSize = num;
    return ret;
}

int main()
{
    return 0;
}
