;
; File generated by cc65 v 2.19 - Git 7979f8a41
;
	.fopt		compiler,"cc65 v 2.19 - Git 7979f8a41"
	.setcpu		"6502"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.forceimport	__STARTUP__
	.import		_printf
	.import		_scanf
	.export		_main

.segment	"RODATA"

S0001:
	.byte	$45,$6E,$74,$65,$72,$20,$61,$20,$70,$6F,$73,$69,$74,$69,$76,$65
	.byte	$20,$69,$6E,$74,$65,$67,$65,$72,$3A,$20,$00
S0003:
	.byte	$25,$64,$0A,$00
S0002:
	.byte	$25,$64,$00

; ---------------------------------------------------------------
; int __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

;
; int n = 0 ;
;
	jsr     push0
;
; printf("Enter a positive integer: ") ;
;
	lda     #<(S0001)
	ldx     #>(S0001)
	jsr     pushax
	ldy     #$02
	jsr     _printf
;
; scanf("%d", &n) ;
;
	lda     #<(S0002)
	ldx     #>(S0002)
	jsr     pushax
	lda     #$02
	jsr     leaa0sp
	jsr     pushax
	ldy     #$04
	jsr     _scanf
;
; while (n > 1){
;
	jmp     L0004
;
; if (n & 1){
;
L0002:	ldy     #$00
	lda     (sp),y
	and     #$01
	beq     L0006
;
; n = ((n << 1) + n + 1) >> 1 ;      
;
	jsr     ldax0sp
	jsr     aslax1
	sta     ptr1
	stx     ptr1+1
	jsr     ldax0sp
	clc
	adc     ptr1
	pha
	txa
	adc     ptr1+1
	tax
	pla
	jsr     incax1
;
; else {
;
	jmp     L000A
;
; n = n >> 1 ;
;
L0006:	jsr     ldax0sp
L000A:	jsr     asrax1
	jsr     stax0sp
;
; printf("%d\n", n) ;
;
	lda     #<(S0003)
	ldx     #>(S0003)
	jsr     pushax
	ldy     #$05
	jsr     pushwysp
	ldy     #$04
	jsr     _printf
;
; while (n > 1){
;
L0004:	jsr     ldax0sp
	cmp     #$02
	txa
	sbc     #$00
	bvs     L0005
	eor     #$80
L0005:	bmi     L0002
;
; return 0 ;
;
	ldx     #$00
	txa
;
; }
;
	jmp     incsp2

.endproc

