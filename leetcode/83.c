#include <stdio.h>

Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode *p;

    if (NULL == head) return NULL;

    p = head;
    while (NULL != p->next) {
        while (p->val == p->next->val) {
            p->next = p->next->next;
        }
        if (p->next != NULL) {
            p = p->next;
        }
    }
    return head;
}
int main()
{
    return 0;
}
