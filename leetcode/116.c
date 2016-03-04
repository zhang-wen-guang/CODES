#include <stdio.h>

//Definition for binary tree with next pointer.
struct TreeLinkNode {
 int val;
 struct TreeLinkNode *left, *right, *next;
};


void connect(struct TreeLinkNode *root) {
    struct TreeLinkNode *pre;
    struct TreeLinkNode *cur;

    if (NULL == root) return;
    pre = root;
    cur = NULL;

    while (NULL != pre->left) {
        cur = pre;
        while (cur) {
            cur->left->next = cur->right;
            if (NULL != cur->next)
                cur->right->next = cur->next->left;
            cur = cur->next;
        }
        pre = pre->left;
    }
}

int main()
{
    return 0;
}
