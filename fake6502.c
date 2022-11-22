#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "circuit.h"
#include "reg.h"
#include "bus.h"
#include "tristate.h"
#include "counter.h"

#include "RAM.h"
#include "ALU.h"
#include "STATUS.h"


bus<8> DATA, ADDRh, ADDRl ;
tristate<8> Ah2D, Al2D ;
output<1> Ah2D_e(1), Al2D_e(1) ;

reg<8> EAh, EAl ;
counter<8> SP, PCh, PCl ;
tristate<8> SPht, SPlt, PCht, PClt ;
output<8> SPh_v ;
output<1> EAh_s("2"), EAh_e(1), EAl_s("4"), EAl_e(1), PCh_s("6"), PC_e(1), PCl_s("8"), 
    SP_s("11"), SP_e(1) ;
output<1> SP_down("37"), SP_up, PC_up("38"), PC_down, SP_clear, PC_clear ;

RAM RAM ;
output<1> RAM_s("13"), RAM_e(1) ;

reg<8> ACC ;
output<1> ACC_s("15"), ACC_e(1) ;
reg<8> A, B ;
output<1> A_s("17"), A_e(1), B_s("18"), B_e(1) ;
reg<8> X, Y ;
output<1> X_s("19"), X_e(1), Y_s("21"), Y_e(1) ;

ALU ALU ;
output<4> ALU_op("23,24,25,26") ;
tristate<8> ALU2D ;
output<1> ALU_e(1) ;

STATUS STATUS ;
output<1> STATUS_NZ_s("29"), STATUS_V_s("30"), STATUS_C_s("31"), STATUS_ALU_C_s("32"), STATUS_ALU_C_from_C("33"), STATUS_s ;
output<1> STATUS_e, STATUS_src("36") ;

reg<8> INST ;
output<1> INST_s("37"), INST_e(1) ;


void init6502(){
    ADDRh.data_out.connect(Ah2D.data_in) ;
    Ah2D_e.connect(Ah2D.enable) ;
    Ah2D.data_out.connect(DATA.data_in) ;
    ADDRl.data_out.connect(Al2D.data_in) ;    
    Al2D_e.connect(Al2D.enable) ;
    Al2D.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(RAM.data_in) ;
    ADDRh.data_out.connect(RAM.addrh) ;
    ADDRl.data_out.connect(RAM.addrl) ;
    RAM_e.connect(RAM.enable) ;
    RAM_s.connect(RAM.set) ;
    RAM.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(EAh.data_in) ;
    EAh_e.connect(EAh.enable) ;
    EAh_s.connect(EAh.set) ;
    EAh.data_out.connect(ADDRh.data_in) ;

    DATA.data_out.connect(EAl.data_in) ;
    EAl_e.connect(EAl.enable) ;
    EAl_s.connect(EAl.set) ;
    EAl.data_out.connect(ADDRl.data_in) ;

    PC_up = 1 ;
    PC_down = 1 ;
    DATA.data_out.connect(PCl.data_in) ;
    PCl_s.connect(PCl.load) ;
    PC_up.connect(PCl.up) ;
    PC_down.connect(PCl.down) ;
    PC_clear.connect(PCl.clear) ;
    PCl.data_out.connect(PClt.data_in) ;
    PC_e.connect(PClt.enable) ;
    PClt.data_out.connect(ADDRl.data_in) ;

    DATA.data_out.connect(PCh.data_in) ;
    PCh_s.connect(PCh.load) ;
    PCl.co.connect(PCh.up) ;
    PCl.bo.connect(PCh.down) ;
    PC_clear.connect(PCh.clear) ;
    PCh.data_out.connect(PCht.data_in) ;
    PC_e.connect(PCht.enable) ;
    PCht.data_out.connect(ADDRh.data_in) ;

    SP_up = 1 ;
    SP_down = 1 ;
    DATA.data_out.connect(SP.data_in) ;
    SP_s.connect(SP.load) ;
    SP_up.connect(SP.up) ;
    SP_down.connect(SP.down) ;
    SP_clear.connect(SP.clear) ;
    SP.data_out.connect(SPlt.data_in) ;
    SP_e.connect(SPlt.enable) ;
    SPlt.data_out.connect(ADDRl.data_in) ;

    SPh_v.connect(SPht.data_in) ;
    SPh_v = 0x01 ;
    SP_e.connect(SPht.enable) ;
    SPht.data_out.connect(ADDRh.data_in) ;

    DATA.data_out.connect(ACC.data_in) ;
    ACC_e.connect(ACC.enable) ;
    ACC_s.connect(ACC.set) ;
    ACC.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(A.data_in) ;
    A_e.connect(A.enable) ;
    A_s.connect(A.set) ;
    A_e = 0 ; // always enabled 

    DATA.data_out.connect(B.data_in) ;
    B_e.connect(B.enable) ;
    B_s.connect(B.set) ;
    B_e = 0 ; // always enabled  

    DATA.data_out.connect(X.data_in) ;
    X_e.connect(X.enable) ;
    X_s.connect(X.set) ;
    X.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(Y.data_in) ;
    Y_e.connect(Y.enable) ;
    Y_s.connect(Y.set) ;
    Y.data_out.connect(DATA.data_in) ;

    A.data_out.connect(ALU.a) ;
    B.data_out.connect(ALU.b) ;
    STATUS.alu_c.connect(ALU.c_in) ;
    ALU_op.connect(ALU.op) ;
    ALU.res.connect(ALU2D.data_in) ;
    ALU_e.connect(ALU2D.enable) ;
    ALU2D.data_out.connect(DATA.data_in) ;
    ALU.n.connect(STATUS.n_in) ;
    ALU.v.connect(STATUS.v_in) ;
    ALU.z.connect(STATUS.z_in) ;
    ALU.c.connect(STATUS.c_in) ;

    STATUS_NZ_s.connect(STATUS.nz_set) ;
    STATUS_V_s.connect(STATUS.v_set) ;
    STATUS_C_s.connect(STATUS.c_set) ;
    STATUS_ALU_C_s.connect(STATUS.alu_c_set) ;
    STATUS_ALU_C_from_C.connect(STATUS.alu_c_from_C) ;
    STATUS_s.connect(STATUS.set) ;
    STATUS_e.connect(STATUS.data_enable) ;
    STATUS_src.connect(STATUS.src_data) ;
    DATA.data_out.connect(STATUS.data_in) ;
    STATUS.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(INST.data_in) ;
    INST_s.connect(INST.set) ;
    INST_e.connect(INST.enable) ;
    INST_e = 0 ; // always enabled
}


#include "addrmodes.h"
#include "ops.h"


//undocumented instructions
#define lax nop
#define sax nop
#define dcp nop
#define isb nop
#define slo nop
#define rla nop
#define sre nop
#define rra nop


static uint8_t (*addrtable[256])(uint8_t tick) = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |     */
/* 0 */     imp, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, abso, /* 0 */
/* 1 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx, /* 1 */
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
};

static uint8_t (*optable[256])(uint8_t tick) = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |      */
/* 0 */      brk,  ora,  rst,  slo,  nop,  ora,  asl,  slo,  php,  ora,  asl,  nop,  nop,  ora,  asl,  slo, /* 0 */
/* 1 */      bpl,  ora,  nop,  slo,  nop,  ora,  asl,  slo,  clc,  ora,  nop,  slo,  nop,  ora,  asl,  slo, /* 1 */
/* 2 */      jsr,  and_,  nop,  rla,  bit,  and_,  rol,  rla,  plp,  and_,  rol,  nop,  bit,  and_,  rol,  rla, /* 2 */
/* 3 */      bmi,  and_,  nop,  rla,  nop,  and_,  rol,  rla,  sec,  and_,  nop,  rla,  nop,  and_,  rol,  rla, /* 3 */
/* 4 */      rti,  eor,  nop,  sre,  nop,  eor,  lsr,  sre,  pha,  eor,  lsr,  nop,  jmp,  eor,  lsr,  sre, /* 4 */
/* 5 */      bvc,  eor,  nop,  sre,  nop,  eor,  lsr,  sre,  cli,  eor,  nop,  sre,  nop,  eor,  lsr,  sre, /* 5 */
/* 6 */      rts,  adc,  nop,  rra,  nop,  adc,  ror,  rra,  pla,  adc,  ror,  nop,  jmp,  adc,  ror,  rra, /* 6 */
/* 7 */      bvs,  adc,  nop,  rra,  nop,  adc,  ror,  rra,  sei,  adc,  nop,  rra,  nop,  adc,  ror,  rra, /* 7 */
/* 8 */      nop,  sta,  nop,  sax,  sty,  sta,  stx,  sax,  dey,  nop,  txa,  nop,  sty,  sta,  stx,  sax, /* 8 */
/* 9 */      bcc,  sta,  nop,  nop,  sty,  sta,  stx,  sax,  tya,  sta,  txs,  nop,  nop,  sta,  nop,  nop, /* 9 */
/* A */      ldy,  lda,  ldx,  lax,  ldy,  lda,  ldx,  lax,  tay,  lda,  tax,  nop,  ldy,  lda,  ldx,  lax, /* A */
/* B */      bcs,  lda,  nop,  lax,  ldy,  lda,  ldx,  lax,  clv,  lda,  tsx,  lax,  ldy,  lda,  ldx,  lax, /* B */
/* C */      cpy,  cmp,  nop,  dcp,  cpy,  cmp,  dec,  dcp,  iny,  cmp,  dex,  nop,  cpy,  cmp,  dec,  dcp, /* C */
/* D */      bne,  cmp,  nop,  dcp,  nop,  cmp,  dec,  dcp,  cld,  cmp,  nop,  dcp,  nop,  cmp,  dec,  dcp, /* D */
/* E */      cpx,  sbc,  nop,  isb,  cpx,  sbc,  inc,  isb,  inx,  sbc,  nop,  sbc,  cpx,  sbc,  inc,  isb, /* E */
/* F */      beq,  sbc,  nop,  isb,  nop,  sbc,  inc,  isb,  sed,  sbc,  nop,  isb,  nop,  sbc,  inc,  isb  /* F */
};


int do_inst(){
    uint8_t addr_start = 0, op_start = 0 ;
    bool fetch_done = false, addr_done = false, op_done = false ;
    int step = 0 ;
    for (; step < 16 ; step++){
        for (int phase = 0 ; phase < 4 ; phase++){
            uint8_t tick = step << 4 | phase ;
            if (! fetch_done){
                if (fetch(tick)){
                    continue ;
                } 
                fetch_done = true ;
                addr_start = step << 4 ;
            }
            if (! addr_done){
                if ((*addrtable[INST])(tick - addr_start)){
                    continue ;
                }
                addr_done = true ;
                op_start = step << 4 ;
            }
            if (! op_done){
                if ((*optable[INST])(tick - op_start)){
                    continue ;
                }
                return step ;
            }
        }
    }

    return step ;
}


void reset6502(){
    PC_clear.pulse() ;
    DATA.data_out = 0x02 ; // RST instruction
    PC_e.toggle() ; RAM_s.toggle() ;
    PC_e.toggle() ; RAM_s.toggle() ;
    DATA.data_out = 0 ;
    do_inst() ;
    PC_clear.pulse() ;
    printf("RESET -> PC:0x%02X%02X, SP:0x%X, STATUS:0x%02X\n", (uint8_t)PCh, (uint8_t)PCl, (uint8_t)SP, (uint8_t)STATUS.sreg) ;
}


void load6502(uint8_t prog[], int prog_len){
    PC_clear.pulse() ;
    for (int i = 0 ; i < prog_len ; i++){
        DATA.data_out = prog[i] ;
        PC_e.toggle() ; RAM_s.toggle() ;
        PC_e.toggle() ; RAM_s.toggle() ;
        DATA.data_out = 0 ;
        PC_up.pulse() ;
    }
    PC_clear.pulse() ;
    printf("LOAD  -> %d bytes loaded starting at address 0x00 (PC is now 0x%02X%02X)\n", prog_len, (uint8_t)PCh, (uint8_t)PCl) ;
}


int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Usage: %s SUCCESS_ADDR_IN_HEX\n", argv[0]) ;
        exit(1) ;
    }

    uint16_t SUCCESS_ADDR = (uint16_t)strtol(argv[1], NULL, 16) ;
    printf("Success address is 0x%X\n", SUCCESS_ADDR) ;

    init6502() ;

    // Here the reset sequence begins...
    reset6502() ;

    // Load the program to RAM
    FILE *file = fopen("6502_functional_test.bin", "rb") ; 
    uint8_t prog[0x10000] ;
    int prog_len = fread(prog, 1, 0x10000, file) ;
    fclose(file) ;
    load6502(prog, prog_len) ;

    // Start processing instructions.
    int nb_inst = 0, nb_step = 0 ;
    while (1) {
        if ((PCh.data_out << 8 | PCl.data_out) == SUCCESS_ADDR){
            printf("SUCCESS (%d instructions executed in %d steps)!\n", nb_inst, nb_step) ;
            exit(0) ;
        }

        nb_step += do_inst() ;
        nb_inst++ ;
    }
}