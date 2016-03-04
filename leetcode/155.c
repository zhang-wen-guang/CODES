#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *a;
    int top;
    int min, size;
} MinStack;

void minStackCreate(MinStack *stack, int maxSize) {
    stack->a = (int *)malloc(maxSize * sizeof(int));
    stack->top = 0;
    stack->min = 0;
    stack->size = 0;
}

void minStackPush(MinStack *stack, int element) {
    (stack->a)[stack->top++] = element;
    if (0 == stack->size) stack->min = element;
    if (element < stack->min) stack->min = element;
    stack->size++;
}

void minStackPop(MinStack *stack) {
    int i;
    stack->top--;
    stack->size--;
    if (0 != stack->size) {
        stack->min = (stack->a)[0];
        for (i = 0; i < stack->size; ++i) {
            if ((stack->a)[i] < stack->min) stack->min = (stack->a)[i];
        }
    }
}

int minStackTop(MinStack *stack) {
    return (stack->a)[stack->top - 1];
}

int minStackGetMin(MinStack *stack) {
    return stack->min;
}

void minStackDestroy(MinStack *stack) {
    free(stack->a);
}

int main()
{
    MinStack stack;
    minStackCreate(&stack, 1000);
    printf("stack size = %d\n", stack.size);
    printf("stack top = %d\n", minStackTop(&stack));
    printf("stack min = %d\n", minStackGetMin(&stack));
    printf("bingo\n");
    for (int i = 0; i < 100; ++i) {
        minStackPush(&stack, i + 1);
    }
    printf("bingo2\n");
    printf("stack top = %d\n", minStackTop(&stack));
    printf("stack min = %d\n", minStackGetMin(&stack));
    printf("stack size = %d\n", stack.size);
    minStackDestroy(&stack);
    return 0;
}
