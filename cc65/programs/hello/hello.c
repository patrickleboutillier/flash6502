
#include <string.h>
#include <stdio.h>
#include <unistd.h>


#define STDOUT 0xFFF1


void print(char *str){
    int i = 0 ;
    while (str[i] != '\0'){
        *(char *)STDOUT = str[i++] ;
    }
}


int main(){
    char buf[16] ;
    
    // Adding this string copy breaks the program...
    strcpy(buf, "test\n") ;

    print(buf) ;
    print("12\n") ;

    return 0 ;
}