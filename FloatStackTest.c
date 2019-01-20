#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "FloatStack.h"

#define EPSILON 0.00001

int main(void){
    stackfloat* s = stackInitFloat(10);
    int i;

    assert(isEmptyFloat(s));
    assert(isFullFloat(s) == 0);

    for (i = 0; i < 10; i++){
        pushFloat(s, 1.1);
    }
    
    assert(isFullFloat(s));
    assert(isEmptyFloat(s) == 0);
    assert(fabs(popFloat(s) - 1.1) < EPSILON);
    assert(isEmptyFloat(s) == 0);
    assert(isFullFloat(s) == 0);
    for (i = 0; i < 9; i++){
        assert(fabs(popFloat(s) - 1.1) < EPSILON);
    }

    /* pop(s); pop an empty stack
    exit with code 1 -> as expected */

    assert(isEmptyFloat(s));
    freeStackFloat(s);
}
