
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../flash6502.h"


int main(){
    int n = 0, i = 0 ;
    long sum = 0 ;

    printf("stdout: %d\n", 134 / 56) ;
    fprintf(stdout, "stdout via fd\n") ;
    fprintf(stderr, "stderr via fd\n") ;


    printf("Enter a positive integer: ");
    scanf("%d", &n);

    for (i = 1; i <= n; ++i) {
        sum += i;
    }

    printf("Sum = %ld\n", sum);
    return 0 ;
}