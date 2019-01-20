#include <stdio.h>
#include "parser_extension.h"
#include "dict.h"
#include <assert.h>
#include <string.h>

#define MAX_STR 1024
#define MAX_STACK 100

#define EPSILON 0.0000001

bool strComp(char* str1, char* str2);
void BEGIN(pro* p, dict* d, stack* s);
void INSTRCTLIST(pro* p, dict* d, stack* s);
void INSTRUCTION(pro* p, dict* d, stack* s);
void FD(pro* p, dict* d);
void LT(pro* p, dict* d);
void RT(pro* p, dict* d);
void DO(pro* p, dict* d, stack* s);
void SET(pro* p, dict* d, stack* s);
mydataType VARNUM(pro* p, dict* d);
void POLISH(pro* p, dict* d, stack* s);
bool isOP(char* s);
void CIR(pro* p, dict* d);

void parse_extension(FILE *fp){
    stack* s; /* parenthesis stack */
    dict* d;
    int i;
    pro program;
    program.st = stackInitFloat(MAX_STACK); /* calculate stack */
    if (program.st == NULL) {
        exit(2);
    }
    s = stackInit(MAX_STACK);
    d = dictInit();
    init(&program.w);
    
    program.cursor = 0;
    for (i = 0; i < MAXMUMTOKENS; i++) {
        program.words[i][0] = '\0';
    }
    i = 0;
    while (fscanf(fp, "%s", program.words[i++]) == 1 && i < MAXMUMTOKENS);
    assert(i < MAXMUMTOKENS);
    BEGIN(&program, d, s);
    
    if (!isEmpty(s)) {
        printf("Parenthesis not matched\n");
        exit(1);
    }

    while(!program.w.finished){
        exitEvent(&program.w);
    }
    
    freeDict(d);
    freeStack(s);
    freeStackFloat(program.st);

    SDL_Quit();
    atexit(SDL_Quit);
}

void BEGIN(pro* p, dict* d, stack* s){
    if(!strComp(p->words[p->cursor], "{")){
        exit(1);
    }
    push(s, '{');
    p->cursor += 1;
    INSTRCTLIST(p, d, s);
}

void INSTRCTLIST(pro* p, dict* d, stack* s){
    if (strComp(p->words[p->cursor], "}")) {
        if (pop(s) != '{') {
            printf("Parenthesis not matched\n");
            exit(1);
        }
        return;
    }
    INSTRUCTION(p, d, s);
    p->cursor += 1;
    INSTRCTLIST(p, d, s);
}

void INSTRUCTION(pro* p, dict* d, stack* s){
    if (strComp(p->words[p->cursor], "FD")){
        FD(p, d);
        return;
    }else if (strComp(p->words[p->cursor], "LT")){
        LT(p, d);
        return;
    }else if (strComp(p->words[p->cursor], "RT")){
        RT(p, d);
        return;
    }else if (strComp(p->words[p->cursor], "DO")){
        DO(p, d, s);
        return;
    }else if (strComp(p->words[p->cursor], "SET")){
        SET(p, d, s);
        return;
    }else if (strComp(p->words[p->cursor], "CIR")){
        CIR(p, d);
        return;
    }else{
        printf("Instruction Wrong\n");
        exit(1);
    }
}

void FD(pro* p, dict* d){
    int var;
    p->cursor += 1;
    var = VARNUM(p, d);
    /* execution */
    /* printf("Doing FD! Go foward %d\n", var); */
    drawLine(&p->w, var);
}
void LT(pro* p, dict* d){
    int var;
    p->cursor += 1;
    var = VARNUM(p, d);
    /* execution */
    p->w.angle -= var;
    /* printf("Doing LT! Now angle is %d\n", p->w.angle); */
}
void RT(pro* p, dict* d){
    int var;
    p->cursor += 1;
    var = VARNUM(p, d);
    /* execution */
    p->w.angle += var;
    /* printf("Doing RT! Now angle is %d\n", p->w.angle); */
}

void CIR(pro* p, dict* d){
    int radius;
    p->cursor += 1;
    radius = VARNUM(p, d);
    /* execution */
    drawCircleWithoutFilling(&p->w, p->w.current_x, p->w.current_y, radius);
}

void DO(pro* p, dict* d, stack* s){
    int start, end;
    char var;
    int cur;
    char variable[MAXTOKENSIZE];
    p->cursor += 1; /* To VAR */
    var = p->words[p->cursor][0];
    if (!(var >= 'A' && var <= 'Z')) {
        printf("Variable name illegle\n");
        exit(1);
    }
    strcpy(variable, p->words[p->cursor]);
    p->cursor += 1; /* To FROM */
    if (!(strComp(p->words[p->cursor], "FROM"))) {
        printf("Grammar wrong\n");
        exit(1);
    }
    p->cursor += 1; /* To VARNUM */
    start = VARNUM(p, d);
    if (!isIn(d, variable)) {
        dictInsert(d, variable, start);
    }else{
        updateValue(d, variable, start);
    }
    p->cursor += 1; /* To TO */
    if (!(strComp(p->words[p->cursor], "TO"))) {
        printf("Grammar wrong\n");
        exit(1);
    }
    p->cursor += 1; /* To VARNUM */
    end = VARNUM(p, d);
    p->cursor += 1; /* To { */
    if (!(strComp(p->words[p->cursor], "{"))) {
        printf("Grammar wrong\n");
        exit(1);
    }
    push(s, '{');
    p->cursor += 1; /* To INSTRCTLIST */
    cur = p->cursor;
    for (; getValueByKey(d, variable) <= end; updateValue(d, variable, getValueByKey(d, variable)+1)) {
        p->cursor = cur; /* Go back to the first instruction inside loop */
        INSTRCTLIST(p, d, s);
        if (end - getValueByKey(d, variable) > EPSILON) {
            push(s, '{');
        }
    }
}
void SET(pro* p, dict* d, stack* s){
    char letter = p->words[p->cursor][0];
    char var[MAXTOKENSIZE];
    /* Cursor -> "SET" */
    p->cursor += 1; /* To VAR */
    if (letter <= 'Z' && letter >= 'A') {
        strcpy(var, p->words[p->cursor]);
    }else{
        printf("Variable name illegal\n");
        exit(1);
    }
    p->cursor += 1; /* To := */
    if (!strComp(p->words[p->cursor], ":=")) {
        printf("Assignment symbol wrong, check\n");
        exit(1);
    }
    p->cursor += 1; /* To POLISH */
    /* polish */
    POLISH(p, d, s);
    if (isIn(d, var)) {
        updateValue(d, var, popFloat(p->st));
    }else{
        dictInsert(d, var, popFloat(p->st));
    }
}

void POLISH(pro* p, dict* d, stack* s){
    /* first char in POLISH */
    float cal1, cal2;
    /* ; */
    if (strComp(p->words[p->cursor], ";")) {
        return;
    }else if (isOP(p->words[p->cursor])) {
        /* OP */
        cal2 = popFloat(p->st);
        cal1 = popFloat(p->st);
        switch (p->words[p->cursor][0]) {
            case '+':
                pushFloat(p->st, cal1+cal2);
                break;
            case '-':
                pushFloat(p->st, cal1-cal2);
                break;
            case '*':
                pushFloat(p->st, cal1*cal2);
                break;
            case '/':
                if (cal2 > 0 || cal2 < 0) {
                    pushFloat(p->st, cal1/cal2);
                }else{
                    printf("Denominator cannot be 0!\n");
                    exit(3);
                }
            default:
                break;
        }
        p->cursor += 1;
        POLISH(p, d, s);
        return;
    }else{
        pushFloat(p->st, VARNUM(p, d));
        p->cursor += 1;
        POLISH(p, d, s);
        return;
    }
}

bool isOP(char* s){
    if (strComp(s, "-") || strComp(s, "+") || strComp(s, "*") || strComp(s, "/")) {
        return TRUE;
    }
    return FALSE;
}

mydataType VARNUM(pro* p, dict* d){
    char letter = p->words[p->cursor][0];
    if (letter <= 'Z' && letter >= 'A') {
        if (isIn(d, p->words[p->cursor])) {
            return getValueByKey(d, p->words[p->cursor]);
        }else{
            printf("Used undefined variable\n");
            exit(1);
        }
    }
    return atof(p->words[p->cursor]);
}

bool strComp(char* str1, char* str2){
    if (strcmp(str1, str2) == 0) {
        return TRUE;
    }
    return FALSE;
}
