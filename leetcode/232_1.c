#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define bool int

typedef struct listNode{
    int val;
    struct listNode *next;
} listNode;

typedef struct{
    struct listNode *head;
    struct listNode *tail;
    int maxsize;
    int size;
} Queue;

void queueCreate(Queue *queue, int maxSize) {
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    queue->maxsize = maxSize;
}

/* Push element x to the back of queue */
void queuePush(Queue *queue, int element) {
    listNode *node;

    node = (listNode *)malloc(sizeof(listNode));
    node->val = element;

    if (queue->size == 0) {
        queue->tail = node;
        queue->head = node;
        queue->size = 1;
        return;
    }
    queue->tail->next = node;
    node->next = NULL;
    queue->tail = node;
    queue->size++;
}

/* Removes the element from front of queue */
void queuePop(Queue *queue) {
    if (0 == queue->size) return;
    listNode *tmp;
    tmp = queue->head;
    queue->head = queue->head->next;
    if (1 == queue->size) queue->tail = NULL;
    queue->size--;
    free(tmp);
}

/* Get the front element */
int queuePeek(Queue *queue) {
    if (0 == queue->size) return 0;
    return queue->head->val;
}

/* Return whether the queue is empty */
bool queueEmpty(Queue *queue) {
    if (0 == queue->size)
        return true;
    else
        return false;
}

/* Destroy the queue */
void queueDestroy(Queue *queue) {
    if (0 == queue->size) return;
    while (queue->size) queuePop(queue);
}

int main()
{
    Queue q;
    queueCreate(&q, 100);
    for (int i = 0; i < 10; ++i) {
        queuePush(&q, i);
    }
    printf("Bingo\n");
    for (int i = 0; i < 10; ++i) {
        queuePop(&q);
    }
    return 0;
}
