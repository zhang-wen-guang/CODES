#include <stdio.h>


//Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode *p, *tmp;

    if (NULL == head) return NULL;
    if (head->next == NULL) return head;

    p = head->next;
    tmp = head;
    tmp ->next = p->next;
    p->next = tmp;
    head = p;
    p = head->next;

    while (NULL != p->next && NULL != p->next->next) {
        tmp = p->next;
        p->next = tmp->next;
        tmp ->next = p->next->next;
        p->next->next = tmp;
        p = p->next->next;
    }
    return head;
}

int main()
{
    return 0;
}
