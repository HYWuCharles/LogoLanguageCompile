#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Stack.h"

int main(void){
    stack* s = stackInit(10);
    int i;

    assert(isEmpty(s));
    assert(isFull(s) == 0);

    for (i = 0; i < 10; i++){
        push(s, '(');
    }
    
    assert(isFull(s));
    assert(isEmpty(s) == 0);
    assert(pop(s) == '(');
    assert(isEmpty(s) == 0);
    assert(isFull(s) == 0);
    for (i = 0; i < 9; i++){
        assert(pop(s) == '(');
    }

    /* pop(s); pop an empty stack
    exit with code 1 -> as expected */

    assert(isEmpty(s));
    freeStack(s);
}
