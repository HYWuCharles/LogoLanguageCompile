#ifndef Stack_h
#define Stack_h

#include <stdio.h>
#include <stdlib.h>

typedef char elementType;

typedef struct STACK{
    int capacity;
    int stackTop;
    elementType* stackArr;
}stack;

int isEmpty(stack *s);
int isFull(stack *s);
stack* stackInit(int maxCap);
void freeStack(stack *s);
elementType pop(stack *s);
void push(stack *s, elementType e);

#endif /* Stack_h */
