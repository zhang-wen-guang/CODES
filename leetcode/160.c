#include <stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode *p1, *p2;

    p1 = headA;
    p2 = headB;

    if (NULL == p1 || NULL == p2) return NULL;

    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
        if (p1 == p2) return p1;
        if (NULL == p1) p1 = headB;
        if (NULL == p2) p2 = headA;
    }
    return p1;
}

int main()
{
    return 0;
}
