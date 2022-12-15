
STDOUT = $FFF1


	.org $0000

star:
	.byte     "*       *", $0a
	.byte "    **     **", $0a
	.byte "    ***   ***", $0a
	.byte "    **** ****", $0a
	.byte "*****************", $0a
	.byte " ***************", $0a
	.byte "  *************", $0a
	.byte "   ***********", $0a
	.byte "    *********", $0a
	.byte "   ***********", $0a
	.byte "  *************", $0a
	.byte " ***************", $0a
	.byte "*****************", $0a
	.byte "    **** ****", $0a
	.byte "    ***   ***", $0a
	.byte "    **     **", $0a
	.byte "    *       *", $0a

ptr:
	.word star		; initialize ptr to star which is $0000


	.org $0100

main:
	; print ' '
	lda #32
	sta STDOUT
	sta STDOUT
	sta STDOUT
	sta STDOUT

	ldy #0
loop:				
	lda (ptr),y
	beq next		; the loop will overrun into ptr (which is 0), so we skip the 0 bytes
	sta STDOUT
next:
	iny
	bne loop
done:
	jmp *




