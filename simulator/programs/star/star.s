
STDOUT = $FFF1
HALT   = $FFF9


	.org $0000
	.byte 0x00		; skip, $0000 clobbered by CPU at reset
ptr:
	.word star		; initialize ptr to star which is $0200


	.org $0200 
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


	.org $0300
main:
	; print ' '
	lda #' '
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
	sta HALT


nmi:
irq:
	rti

	.org $fffa
  	.word nmi
  	.word main
  	.word irq




