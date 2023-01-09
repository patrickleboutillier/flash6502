
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../flash6502.h"


char buf[16] ;

int main(){
    //char buf[16] ;
    //strcpy(buf, "test\n") ;
    //print(buf) ;

    itoa(42, buf, 10) ;
    strcat(buf, "\n") ;
    print(buf) ;

    return 0 ;
}