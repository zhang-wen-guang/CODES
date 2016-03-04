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
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    struct TreeNode *stack[1000];
    struct TreeNode *tmp;
    int top = 0;
    int a[1000];
    int num = 0;
    int *ret;

    if (NULL != root) stack[top++] = root;

    while (0 != top ) {
        if (NULL != stack[top - 1]) {
            stack[top] = stack[top - 1]->left;
            top++;
        } else {
            top--;
            if (0 != top) {
                a[num++] = stack[top - 1]->val;
                tmp = stack[top - 1];
                top--;
                stack[top++] = tmp->right;
            }
        }
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
    int *ret;
    int size;
    struct TreeNode a, b;
    a.val = 1;
    b.val = 2;

    a.left = NULL;
    a.right = NULL;

    b.left = NULL;
    b.right = NULL;

    ret = inorderTraversal(&a, &size);
    printf("size = %d\n", size);
    for (int i = 0; i < size; ++i) {
        printf("%d\n", ret[i]);
    }
    return 0;
}
