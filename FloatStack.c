#include "FloatStack.h"
#define EMPTY -1

void nullStackFloat(stackfloat* s);

stackfloat* stackInitFloat(int maxCap){
    stackfloat *s;
    if (maxCap < 0) {
        printf("Size cannot be negative\n");
        exit(1);
    }
    
    s = (stackfloat*) malloc(sizeof(stackfloat));
    if (s == NULL) {
        printf("Stack created failed\n");
        exit(1);
    }
    s->capacity = maxCap;
    s->stackArr = (E*) malloc(s->capacity*sizeof(E));
    if (s->stackArr == NULL) {
        printf("Stack created failed\n");
        exit(1);
    }
    s->stackTop = EMPTY;
    nullStackFloat(s);
    return s;
}

void nullStackFloat(stackfloat* s){
    int i;
    for (i = 0; i < s->capacity; i++) {
        s->stackArr[i] = '\0';
    }
}

int isEmptyFloat(stackfloat *s){
    return (s->stackTop == EMPTY);
}

int isFullFloat(stackfloat *s){
    return (s->stackTop == s->capacity-1);
}

void freeStackFloat(stackfloat *s){
    if (s != NULL) {
        free(s->stackArr);
        free(s);
        s = NULL;
    }
}

E popFloat(stackfloat *s){
    int i = -1;
    if (!isEmptyFloat(s)) {
        i = s->stackTop;
        s->stackTop--;
    }else{
        printf("Stack is Empty");
        exit(1);
    }
    return s->stackArr[i];
}

void pushFloat(stackfloat *s, E e){
    if (!isFullFloat(s)) {
        s->stackTop++;
        s->stackArr[s->stackTop] = e;
    }else{
        printf("Stack is full!\n");
        exit(1);
    }
}
