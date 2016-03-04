#include <stdio.h>
#include <stdlib.h>

//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrderBottom(struct TreeNode* root, int** columnSizes, int* returnSize) {
    struct TreeNode *a[1000], *b[1000];
    int size_a, size_b, cnt;
    int *p[1000], i, **ret, tmp_size[1000];

    if (NULL == root) return NULL;
    a[0] = root;
    size_a = 1;
    size_b = 0;
    tmp_size[0] = 1;
    p[0] = (int *)malloc(sizeof(int));
    p[0][0] = root->val;
    cnt = 1;
    while (1) {
        for (i = 0; i < size_a; ++i) {
            if (NULL != a[i]->left) {
                b[size_b++] = a[i]->left;
            }
            if (NULL != a[i]->right) {
                b[size_b++] = a[i]->right;
            }
        }
        tmp_size[cnt] = size_b;
        p[cnt] = (int *)malloc(size_b * sizeof(int));
        for (i = 0; i < size_b; ++i) {
            p[cnt][i] = b[i]->val;
            a[i] = b[i];
        }
        size_a = size_b;
        if (0 == size_b) break;
        size_b = 0;
        cnt++;
    }
    ret = (int **)malloc(sizeof(int *) * cnt);
    (*columnSizes) = (int *)malloc(sizeof(int) * cnt);
    for (i = 0; i < cnt; ++i) {
        ret[i] = p[cnt - 1 - i];
        (*columnSizes)[i] = tmp_size[cnt - 1 - i];
    }
    *returnSize = cnt;
    return ret;
}

int main()
{
    int **arr;
    int *col, size;
    struct TreeNode a, b, c, d, e;
    a.val = 3;
    b.val = 9;
    c.val = 20;
    d.val = 15;
    e.val = 7;

    a.left = &b;
    a.right = &c;
    b.left = NULL;
    b.right = NULL;
    c.left = &d;
    c.right = &e;
    d.left = NULL;
    d.right = NULL;
    e.left = NULL;
    e.right = NULL;

    arr = levelOrder(&a, &col, &size);
    printf("Bingo2\n");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < col[i]; ++j) {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
