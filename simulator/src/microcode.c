#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "STATUS.h"
#include "CONTROL_ROMS.h"
#include "ALU.h"

CONTROL_1_ROM C1 ;
CONTROL_2_ROM C2 ;
CONTROL_3_ROM C3 ;
CONTROL_4_ROM C4 ;
CONTROL_5_ROM C5 ;
CONTROL_UNIT CU(&C1, &C2, &C3, &C4, &C5) ;

STATUS STATUS ;
uint8_t INST ;

#include "addrmodes.h"
#include "ops.h"


static uint8_t (*addrtable[256])(uint8_t tick) = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |     */
/* 0 */     imp, indx,  imp, imp,    zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, abso, /* 0 */
/* 1 */     rel, indy,  imp, imp,   imp,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx, /* 1 */
/* 2 */    abso, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, abso, /* 2 */
/* 3 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx, /* 3 */
/* 4 */     imp, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, abso, /* 4 */
/* 5 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx, /* 5 */
/* 6 */     imp, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm,  ind, abso, abso, abso, /* 6 */
/* 7 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx, /* 7 */
/* 8 */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, abso, /* 8 */
/* 9 */     rel, indy,  imp, indy,  zpx,  zpx,  zpy,  zpy,  imp, absy,  imp, absy, absx, absx, absy, absy, /* 9 */
/* A */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, abso, /* A */
/* B */     rel, indy,  imp, indy,  zpx,  zpx,  zpy,  zpy,  imp, absy,  imp, absy, absx, absx, absy, absy, /* B */
/* C */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, abso, /* C */
/* D */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx, /* D */
/* E */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, abso, /* E */
/* F */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx  /* F */
} ;

static uint8_t (*optable[256])(uint8_t tick) = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |      */
/* 0 */      brk,  ora,  rst1, rst2, nop,  ora,  asl,  nop,  php,  ora,  asl,  nop,  nop,  ora,  asl,  nop, /* 0 */
/* 1 */      bpl,  ora,  irq,  nmi,  nop,  ora,  asl,  nop,  clc,  ora,  nop,  nop,  nop,  ora,  asl,  nop, /* 1 */
/* 2 */      jsr,  and_,  nop, nop,  bit_,  and_,  rol,  nop,  plp,  and_,  rol,  nop,  bit_,  and_,  rol,  nop, /* 2 */
/* 3 */      bmi,  and_,  nop, nop,  nop,  and_,  rol,  nop,  sec,  and_,  nop,  nop,  nop,  and_,  rol,  nop, /* 3 */
/* 4 */      rti,  eor,  nop,  nop,  nop,  eor,  lsr,  nop,  pha,  eor,  lsr,  nop,  jmp,  eor,  lsr,  nop, /* 4 */
/* 5 */      bvc,  eor,  nop,  nop,  nop,  eor,  lsr,  nop,  cli_,  eor,  nop,  nop,  nop,  eor,  lsr,  nop, /* 5 */
/* 6 */      rts,  adc,  nop,  nop,  nop,  adc,  ror,  nop,  pla,  adc,  ror,  nop,  jmp,  adc,  ror,  nop, /* 6 */
/* 7 */      bvs,  adc,  nop,  nop,  nop,  adc,  ror,  nop,  sei_,  adc,  nop,  nop,  nop,  adc,  ror,  nop, /* 7 */
/* 8 */      nop,  sta,  nop,  nop,  sty,  sta,  stx,  nop,  dey,  nop,  txa,  nop,  sty,  sta,  stx,  nop, /* 8 */
/* 9 */      bcc,  sta,  nop,  nop,  sty,  sta,  stx,  nop,  tya,  sta,  txs,  nop,  nop,  sta,  nop,  nop, /* 9 */
/* A */      ldy,  lda,  ldx,  nop,  ldy,  lda,  ldx,  nop,  tay,  lda,  tax,  nop,  ldy,  lda,  ldx,  nop, /* A */
/* B */      bcs,  lda,  nop,  nop,  ldy,  lda,  ldx,  nop,  clv,  lda,  tsx,  nop,  ldy,  lda,  ldx,  nop, /* B */
/* C */      cpy,  cmp,  nop,  nop,  cpy,  cmp,  dec,  nop,  iny,  cmp,  dex,  nop,  cpy,  cmp,  dec,  nop, /* C */
/* D */      bne,  cmp,  nop,  nop,  nop,  cmp,  dec,  nop,  cld,  cmp,  nop,  nop,  nop,  cmp,  dec,  nop, /* D */
/* E */      cpx,  sbc,  nop,  nop,  cpx,  sbc,  inc,  nop,  inx,  sbc,  nop,  sbc,  cpx,  sbc,  inc,  nop, /* E */
/* F */      beq,  sbc,  nop,  nop,  nop,  sbc,  inc,  nop,  sed,  sbc,  nop,  nop,  nop,  sbc,  inc,  nop  /* F */
} ;


void generate_microcode(){
    //boot_STEP_clr.pulse() ;
    // At this point, INST is driving the control signals with whatever random value it contains at startup.
    // The enabled control signals when step and phase are both 0 are PC_e and RAM_e (see fetch()).
    // By pulsing the CLK 3 times, we get to STEP 3, where all the control signals have their default values.
    //CLK.pulse() ; CLK.pulse() ; CLK.pulse() ;
    assert(CU.make_cw() == CU.get_default_cw()) ;

    // Disable the step counter so it doesn't mess up our sequencing
    //boot_STEP_cnt_e = 0 ;
    
    printf("uint64_t microcode[] = {\n") ;
    for (int i = 0 ; i < 4096 ; i++){
        uint8_t flags = i & 0b1111 ;
        uint8_t inst = i >> 4 ;

        uint8_t addr_start = 0, op_start = 0 ;
        bool fetch_done = false, addr_done = false ;
        int step = 0 ;
        for (; step < 64 ; step++){
            // Set INST and FLAGS
            INST = inst ;
            STATUS.N = (flags >> 3) & 1 ;
            STATUS.V = (flags >> 2) & 1 ;
            STATUS.Z = (flags >> 1) & 1 ;
            STATUS.C = (flags >> 0) & 1 ;

            if (! fetch_done){
                if (fetch(step)){
                    printf("  /* INST:0x%02X FLAGS:0x%X STEP:%2d */ 0x%010lX,\n", inst, flags, step,
                        CU.make_cw()) ;
                    continue ;
                } 
                fetch_done = true ;
                addr_start = step ;
            }
            if (! addr_done){
                if ((*addrtable[inst])(step - addr_start)){
                    printf("  /* INST:0x%02X FLAGS:0x%X STEP:%2d */ 0x%010lX,\n", inst, flags, step,
                        CU.make_cw()) ;
                    continue ;
                }
                addr_done = true ;
                op_start = step ;
            }
            uint8_t more = (*optable[inst])(step - op_start) ;
            uint64_t cw = (more ? CU.make_cw() : CU.get_default_cw()) ;
            printf("  /* INST:0x%02X FLAGS:0x%X STEP:%2d */ 0x%010lX,\n", inst, flags, step,
                cw) ;
        }
    }
    printf("} ;\n") ;
}


int main(int argc, char *argv[]){
    generate_microcode() ;
}