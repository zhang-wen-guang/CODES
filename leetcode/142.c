#include <stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode *p1, *p2;

    if (NULL == head || NULL == head->next) return NULL;
    p1 = p2 =head;
    while (1) {
        p1 = p1->next;
        p2 = p2->next;
        if (NULL == p2) return NULL;
        p2 = p2->next;
        if (NULL == p2) return NULL;
        if (p1 == p2) break;
    }
    p1 = head;
    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}

int main()
{
    return 0;
}
