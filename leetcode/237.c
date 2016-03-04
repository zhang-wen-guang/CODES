#include <stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void deleteNode(struct ListNode* node) {
    if (NULL == node || NULL == node->next) return;

    while (node->next->next) {
        node->val = node->next->val;
        node = node->next;
    }
    node->val = node->next->val;
    node->next = NULL;
}

int main()
{
    return 0;
}
