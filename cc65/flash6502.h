#ifndef FLASH6502
#define FLASH6502


#include <stdint.h>

#define stdout 0xFFF1
#define stderr 0xFFF2

void fprint(uint16_t fd, char *str) ;
void print(char *str) ;


#endif