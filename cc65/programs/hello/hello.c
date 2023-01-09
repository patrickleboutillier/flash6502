
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../flash6502.h"


int main(){
    printf("stdout: %d\n", 134 / 56) ;
    fprintf(stdout, "stdout via fd\n") ;
    fprintf(stderr, "stderr via fd\n") ;

    return 0 ;
}