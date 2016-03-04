#include <stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode *p, *q;

    p = q = head;
    while (n) {
        q = q->next;
        n--;
    }
    if (q == NULL) return p->next;
    while (q->next) {
        q = q->next;
        p = p->next;
    }
    p->next = p->next->next;
    return head;
}

int main()
{
    return 0;
}
