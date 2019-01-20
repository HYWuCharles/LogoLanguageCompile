#include "Stack.h"
#define EMPTY -1

void nullStack(stack* s);

stack* stackInit(int maxCap){
    stack *s;
    if (maxCap < 0) {
        printf("Size cannot be negative\n");
        exit(1);
    }
    
    s = (stack*) malloc(sizeof(stack));
    if (s == NULL) {
        printf("Stack created failed\n");
        exit(1);
    }
    s->capacity = maxCap;
    s->stackArr = (elementType*) malloc(s->capacity*sizeof(elementType));
    if (s->stackArr == NULL) {
        printf("Stack created failed\n");
        exit(1);
    }
    s->stackTop = EMPTY;
    nullStack(s);
    return s;
}

void nullStack(stack* s){
    int i;
    for (i = 0; i < s->capacity; i++) {
        s->stackArr[i] = '\0';
    }
}

int isEmpty(stack *s){
    return (s->stackTop == EMPTY);
}

int isFull(stack *s){
    return (s->stackTop == s->capacity-1);
}

void freeStack(stack *s){
    if (s != NULL) {
        free(s->stackArr);
        free(s);
        s = NULL;
    }
}

elementType pop(stack *s){
    int i = -1;
    if (!isEmpty(s)) {
        i = s->stackTop;
        s->stackTop--;
    }else{
        printf("Stack is Empty\n");
        exit(1);
    }
    return s->stackArr[i];
}

void push(stack *s, elementType e){
    if (!isFull(s)) {
        s->stackTop++;
        s->stackArr[s->stackTop] = e;
    }else{
        printf("Stack is full!\n");
        exit(1);
    }
}
