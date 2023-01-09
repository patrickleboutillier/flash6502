#include "flash6502.h"


void fprint(uint16_t fd, char *str){
    int i = 0 ;
    while (str[i] != '\0'){
        *(char *)fd = str[i++] ;
    }
}


void print(char *str){
    fprint(stdout, str) ;
}