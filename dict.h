#ifndef dict_h
#define dict_h

#include <stdio.h>
#include <stdlib.h>

#define hashLength 2

#define TRUE 1
#define FALSE 0

typedef float mydataType;

typedef struct Node {
    char* key;
    mydataType value;
    struct Node* next;
}node;

typedef struct Dict {
    node** arr;
    int size;
}dict;

typedef int bool;

dict* dictInit(void);
void dictInsert(dict* d, char* key, mydataType value);
void freeDict(dict* d);
bool isIn(dict* d, char* key);
mydataType getValueByKey(dict* d, char* key);
void updateValue(dict* d, char* key, mydataType value);

#endif /* dict_h */
