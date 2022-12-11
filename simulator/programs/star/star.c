#include <stdio.h>
#include <stdint.h>
#include <string.h>


// Place STAR at 0x0300 
const char *STAR = 
	 "   *       *\n"
	"    **     **\n"
	"    ***   ***\n"
	"    **** ****\n"
	"*****************\n"
	" ***************\n"
	"  *************\n"
	"   ***********\n"
	"    *********\n"
	"   ***********\n"
	"  *************\n"
	" ***************\n"
	"*****************\n"
	"    **** ****\n"
	"    ***   ***\n"
	"    **     **\n"
	"    *       *" ;


// Place pointer in zero page, i.e. 0x10
const char *PTR ;


int main(){
	PTR = STAR ; 				// lda #$03, sta PTR, lda #0, sta PTR+1
	printf(" ") ;

	uint8_t x = 0 ;				// ldx #0
	loop:
	printf("%c", *(PTR + x)) ; 	// lda (PTR,x)
	x++ ;						// inx
	if (x != 0){ 				// bne loop
		goto loop ;
	}
	
	// For terminal only
	printf("\n") ;
}
