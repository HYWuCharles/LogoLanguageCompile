#ifndef FloatStack_h
#define FloatStack_h

#include <stdio.h>
#include <stdlib.h>

typedef float E;

typedef struct STACKFLOAT{
    int capacity;
    int stackTop;
    E* stackArr;
}stackfloat;

int isEmptyFloat(stackfloat *s);
int isFullFloat(stackfloat *s);
stackfloat* stackInitFloat(int maxCap);
void freeStackFloat(stackfloat *s);
E popFloat(stackfloat *s);
void pushFloat(stackfloat *s, E e);

#endif /* FloatStack_h */
