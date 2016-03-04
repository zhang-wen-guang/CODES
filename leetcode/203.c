#include <stdio.h>


//Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode* p;
    p = head;
    if (NULL == p) return NULL;
    while (NULL != p->next) {
        if (p->next->val == val) {
            p->next = p->next->next;
        } else {
            p = p->next;
        }
    }
    if (head->val == val) return head->next;
    return head;
}

int main()
{
    return 0;
}
