#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "dict.h"

#define EPSILON 0.000001

int main(void){
    dict* d = dictInit();
    
    /* Insert into some value */
    /* dictInsert(d, NULL, 0); will exit() */
    dictInsert(d, "A", 10.0);
    dictInsert(d, "B", 20.0);
    dictInsert(d, "C", 10.0);

    assert(fabs(getValueByKey(d, "A") - 10.0) < EPSILON);
    assert(fabs(getValueByKey(d, "B") - 20.0) < EPSILON);
    assert(fabs(getValueByKey(d, "C") - 10.0) < EPSILON);

    assert(isIn(d, "A") == TRUE);
    assert(isIn(d, "B") == TRUE);
    assert(isIn(d, "C") == TRUE);
    assert(isIn(d, "D") == FALSE);

    updateValue(d, "A", 20.0);
    assert(fabs(getValueByKey(d, "A") - 20.0) < EPSILON);
    assert(fabs(getValueByKey(d, "A") - 10.0) > EPSILON);

    /* isIn(NULL, "A"); Program exit with code 1 -> exit as expected */
    freeDict(d);
}
