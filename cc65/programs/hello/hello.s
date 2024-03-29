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
	.import		_stdout
	.import		_stderr
	.import		_fprintf
	.import		_printf
	.import		_scanf
	.export		_main

.segment	"RODATA"

S0004:
	.byte	$45,$6E,$74,$65,$72,$20,$61,$20,$70,$6F,$73,$69,$74,$69,$76,$65
	.byte	$20,$69,$6E,$74,$65,$67,$65,$72,$3A,$20,$00
S0003:
	.byte	$73,$74,$64,$65,$72,$72,$20,$76,$69,$61,$20,$66,$64,$0A,$00
S0002:
	.byte	$73,$74,$64,$6F,$75,$74,$20,$76,$69,$61,$20,$66,$64,$0A,$00
S0001:
	.byte	$73,$74,$64,$6F,$75,$74,$3A,$20,$25,$64,$0A,$00
S0006:
	.byte	$53,$75,$6D,$20,$3D,$20,$25,$6C,$64,$0A,$00
S0005:
	.byte	$25,$64,$00

; ---------------------------------------------------------------
; int __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

;
; int n = 0, i = 0 ;
;
	jsr     push0
	jsr     push0
;
; long sum = 0 ;
;
	jsr     pushl0
;
; printf("stdout: %d\n", 134 / 56) ;
;
	lda     #<(S0001)
	ldx     #>(S0001)
	jsr     pushax
	lda     #$02
	jsr     pusha0
	ldy     #$04
	jsr     _printf
;
; fprintf(stdout, "stdout via fd\n") ;
;
	lda     _stdout
	ldx     _stdout+1
	jsr     pushax
	lda     #<(S0002)
	ldx     #>(S0002)
	jsr     pushax
	ldy     #$04
	jsr     _fprintf
;
; fprintf(stderr, "stderr via fd\n") ;
;
	lda     _stderr
	ldx     _stderr+1
	jsr     pushax
	lda     #<(S0003)
	ldx     #>(S0003)
	jsr     pushax
	ldy     #$04
	jsr     _fprintf
;
; printf("Enter a positive integer: ");
;
	lda     #<(S0004)
	ldx     #>(S0004)
	jsr     pushax
	ldy     #$02
	jsr     _printf
;
; scanf("%d", &n);
;
	lda     #<(S0005)
	ldx     #>(S0005)
	jsr     pushax
	lda     #$08
	jsr     leaa0sp
	jsr     pushax
	ldy     #$04
	jsr     _scanf
;
; for (i = 1; i <= n; ++i) {
;
	ldx     #$00
	lda     #$01
	ldy     #$04
	jsr     staxysp
L0002:	ldy     #$07
	jsr     pushwysp
	ldy     #$09
	jsr     ldaxysp
	jsr     tosicmp
	beq     L0006
	bpl     L0003
;
; sum += i;
;
L0006:	ldy     #$05
	jsr     ldaxysp
	jsr     axlong
	jsr     laddeq0sp
;
; for (i = 1; i <= n; ++i) {
;
	ldy     #$04
	ldx     #$00
	lda     #$01
	jsr     addeqysp
	jmp     L0002
;
; printf("Sum = %ld\n", sum);
;
L0003:	lda     #<(S0006)
	ldx     #>(S0006)
	jsr     pushax
	ldy     #$05
	jsr     ldeaxysp
	jsr     pusheax
	ldy     #$06
	jsr     _printf
;
; return 0 ;
;
	ldx     #$00
	txa
;
; }
;
	jmp     incsp8

.endproc

