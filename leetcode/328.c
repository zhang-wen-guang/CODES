/*************************************************************************
    > File Name: 328.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年03月03日 星期四 13时24分08秒
 ************************************************************************/

#include <stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* oddEvenList(struct ListNode* head) {
    struct ListNode *odd_tail, *even_tail, *even_head, *cur;
    int flag;  //0 means even, 1 means odd

    if (NULL == head) return NULL;
    if (head->next == NULL) return head;

    cur = head->next->next;
    odd_tail = head;
    even_head = head->next;
    even_tail = even_head;
    flag = 1;

    while (cur != NULL) {
        if (1 == flag) {
            odd_tail->next = cur;
            odd_tail = cur;
        } else {
            even_tail->next = cur;
            even_tail = cur;
        }

        flag = 1 - flag;
        cur = cur->next;
    }
    odd_tail->next = even_head;
    even_tail->next = NULL;
    return head;
}

int main()
{
    return 0;
}
