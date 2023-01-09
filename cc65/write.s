;
; Ullrich von Bassewitz, 2003-04-13
;
; int write (int fd, const void* buf, int count);
;

        .export         _write
        .import         popax, popptr1, _FD_BASE
        .importzp       ptr1, ptr2, ptr3, tmp1

.proc   _write

        sta     ptr3
        stx     ptr3+1          ; save count as result

        inx
        stx     ptr2+1
        tax
        inx
        stx     ptr2            ; save count with each byte incremented separately

        jsr     popptr1         ; get buf
        jsr     popax           ; get fd and discard
        tax                     ; store fd in x
L1:     dec     ptr2
        bne     L2
        dec     ptr2+1
        beq     L9
L2:     ldy     #0
        lda     (ptr1),y
L3:     sta     _FD_BASE,x
        inc     ptr1
        bne     L1
        inc     ptr1+1
        jmp     L1

; No error, return count

L9:     lda     ptr3
        ldx     ptr3+1
        rts

.endproc


