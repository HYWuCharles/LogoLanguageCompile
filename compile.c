#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int main(int argc, const char * argv[]) {
    
    FILE *fp;
    
    if (argc != 2) {
        printf("Usage: ./compile <filename>\nCheck your command\n");
        exit(1);
    }
    
    fp = fopen(argv[1], "r");
    printf("%s\n", argv[0]);
    if (fp == NULL) {
        printf("File open failed, program exits\n");
        exit(1);
    }
    
    printf("File open successfully, compiling..\n");
    
    parse(fp);
    fclose(fp);
    
    printf("File compile finished, exit\n");
    
    return 0;
}
