

char *STDOUT = (char *)0xFFF1 ;
char *HALT2 = (char *)0xFFF9 ;

int main(){
    char *hello = "Hello, World!\n" ;
    int i = 0 ;
    for (; hello[i] != '\0' ; i++){
        *STDOUT = hello[i] ;
    }

    return 0 ;
}