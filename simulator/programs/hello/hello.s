
STDOUT = $FFF1
HALT =   $FFF9


	.org $0000
	.byte 0x00		; skip, $0000 clobbered by CPU at reset
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
	sta HALT

nmi:
irq:
	rti

	.org $fffa
  	.word nmi
  	.word main
  	.word irq



