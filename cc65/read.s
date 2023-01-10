;
; 2014-08-22, Greg King
;
; int read (int fd, void* buf, unsigned count);
;

        .export         _read

        .import         popax, popptr1, _FD_BASE
        .importzp       ptr1, ptr2, ptr3


.proc   _read

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
        beq     L9              ; no more room in buf

L2:     lda     _FD_BASE,x      ; get char
        ldy     #0
        sta     (ptr1),y
        inc     ptr1
        bne     L1
        inc     ptr1+1
        bne     L1              ; branch always

; No error, return count.

L9:     lda     ptr3
        ldx     ptr3+1
        rts

.endproc
