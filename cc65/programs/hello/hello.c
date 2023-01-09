
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../flash6502.h"


int main(){
    char buf[16] ;
    strcpy(buf, "test\n") ;
    print(buf) ;

    utoa(42, buf, 10) ;
    strcat(buf, "\n") ;
    print(buf) ;

    return 0 ;
}