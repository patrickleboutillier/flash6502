; ---------------------------------------------------------------------------
; interrupt.s
; ---------------------------------------------------------------------------
;
; Interrupt handler.
;
; Checks for a BRK instruction and returns from all valid interrupts.

.import   _HALT
.export   _irq_int, _nmi_int

.segment  "CODE"


; ---------------------------------------------------------------------------
; Non-maskable interrupt (NMI) service routine

_nmi_int:  RTI                    ; Return from all NMI interrupts

; ---------------------------------------------------------------------------
; Maskable interrupt (IRQ) service routine

_irq_int:  PHA                    ; Save accumulator contents to stack
           TXA                    ; Transfer X to A
           PHA                    ; Save accumulator (X) contents to stack
           TSX                    ; Transfer stack pointer to X
           INX                    ; Increment X so it points to the status
           INX                    ;   register value saved on the stack
           INX
           LDA $100,X             ; Load status register contents
           AND #$10               ; Isolate B status bit
           BNE break              ; If B = 1, BRK detected

; ---------------------------------------------------------------------------
; IRQ detected, return

irq:       PLA                    ; Restore accumulator contents
           TAX                    ; Restore X from accumulator
           PLA                    ; Restore accumulator contents
           RTI                    ; Return from all IRQ interrupts

; ---------------------------------------------------------------------------
; BRK detected, stop

break:     STA _HALT              ; If BRK is detected, something very bad
                                  ;   has happened, so stop running