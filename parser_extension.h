#ifndef parser_extension_h
#define parser_extension_h

#include "FloatStack.h"
#include "Stack.h"
#include "SDLutil.h"

#define MAXMUMTOKENS 1000
#define MAXTOKENSIZE 20

struct Program {
    char words[MAXMUMTOKENS][MAXTOKENSIZE];
    int cursor;
    stackfloat* st;
    Window w;
};

typedef struct Program pro;

void parse_extension(FILE *fp);

#endif /* parser_h */
