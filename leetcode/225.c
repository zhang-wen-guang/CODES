#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

typedef struct {
    int val[1000];
    int top;
} Stack;

/* Create a stack */
void stackCreate(Stack *stack, int maxSize) {
    if (NULL == stack) return;
    stack->top = 0;
}

/* Push element x onto stack */
void stackPush(Stack *stack, int element) {
    if (NULL == stack) return;
    stack->val[stack->top++] = element;
}

/* Removes the element on top of the stack */
void stackPop(Stack *stack) {
    if (NULL == stack) return;
    if (stack->top == 0) return;
    stack->top--;
}

/* Get the top element */
int stackTop(Stack *stack) {
    if (NULL == stack) return 0;
    if (0 == stack->top) return 0;
    return stack->val[stack->top - 1];
}

/* Return whether the stack is empty */
bool stackEmpty(Stack *stack) {
    if (NULL == stack) return true;
    if (0 == stack->top) return true;
    return false;
}

/* Destroy the stack */
void stackDestroy(Stack *stack) {
    return;
}

int main()
{
    Stack stack;

    stackCreate(&stack, 100);
    printf("%d\n", stack.top);
    for (int i = 0; i < 100; ++i) {
        printf("Bingo\n");
        stackPush(&stack, i);
    }
    return 0;
}
