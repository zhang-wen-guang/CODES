#include <stdio.h>


//Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

bool isPalindrome(struct ListNode* head) {
    struct ListNode *slow, *fast;
    struct ListNode *p, *q, *last;

    if (NULL == head) return true;
    slow = fast = head;
    while (NULL != fast->next && NULL != fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    p = slow->next;
    last = NULL;
    if (NULL != p) {
        q = p->next;
        while (NULL != q) {
            p->next = last;
            last = p;
            p = q;
            q = q->next;
        }
        p->next = last;
    }
    slow->next = p;

    fast = slow->next;
    slow = head;
    while (NULL != fast) {
        if (slow->val != fast->val) return false;
        slow = slow->next;
        fast = fast->next;
    }
    return true;
}
int main()
{
    struct ListNode a, b, c, d;
    a.val = 1;
    b.val = 1;
    c.val = 2;
    d.val = 1;
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = NULL;

    isPalindrome(&a);
    return 0;
}
