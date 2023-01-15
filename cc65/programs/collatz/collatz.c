
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../flash6502.h"


int main(){
    int n = 0 ;
    
    printf("Enter a positive integer: ") ;
    scanf("%d", &n) ;

    while (n > 1){
        if (n & 1){
            n = ((n << 1) + n + 1) >> 1 ;      
        }
        else {
            n = n >> 1 ;
        }
        printf("%d\n", n) ;
    }

    return 0 ;
}