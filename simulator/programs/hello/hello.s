
STDOUT = $FFF1

	.org $0000
	jmp main

hello:
	.asciiz "Hello World!", 0xa
ptr:
	.word hello


main:
	ldy #0
loop:				
	lda (ptr),y
	beq done	
	sta STDOUT
	iny
	jmp loop
done:
	jmp *




