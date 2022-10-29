#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "circuit.h"
#include "reg.h"
#include "bus.h"
#include "tristate.h"

#include "RAM.h"
#include "ALU.h"
#include "STATUS.h"


bus<8> DATA, ADDRh, ADDRl ;
tristate<8> Ah2D, Al2D ;
output<1> Ah2D_e("0"), Al2D_e("1") ;

reg<8> EAh, EAl, PCh, PCl, SP ;
tristate<8> SPh ;
output<8> SPh_v ;
output<1> EAh_s("2"), EAh_e("3"), EAl_s("4"), EAl_e("5"), PCh_s("6"), PCh_e("7"), PCl_s("8"), PCl_e("9"), 
    SPh_e("10"), SP_s("11"), SP_e("12") ;

RAM RAM ;
output<1> RAM_s("13"), RAM_e("14") ;


uint8_t MEM_read(uint16_t address){
    return RAM._mem[address >> 8][address & 0xFF] ;
}

uint8_t MEM_readhl(uint8_t addrh, uint8_t addrl){
    return MEM_read(addrh << 8 | addrl) ;
}


void incPC(){
    uint16_t pc = PCh << 8 | PCl ;
    pc++ ;
    PCh = pc >> 8 ;
    PCl = pc & 0xFF ;
}

void incSP(){
    SP = SP + 1 ;
}

void decSP(){
    SP = SP - 1 ;
}


reg<8> ACC ;
output<1> ACC_s("15"), ACC_e("16") ;
reg<8> A, B ;
output<1> A_s("17"), A_e, B_s("18"), B_e ;
reg<8> X, Y ;
output<1> X_s("19"), X_e("20"), Y_s("21"), Y_e("22") ;

ALU ALU ;
output<4> ALU_op("23,24,25,26") ;
tristate<8> ALU2D ;
output<1> ALU_e("27") ;

STATUS STATUS ;
output<1> STATUS_b_in("28") ;
output<1> STATUS_nz_set("29"), STATUS_v_set("30"), STATUS_c_set("31"), STATUS_alu_c_set("32"), STATUS_alu_c_from_C("33") ;
output<1> STATUS_data_enable("34"), STATUS_src_data("35") ;

reg<8> INST ;
output<1> INST_s("36"), INST_e ;
// PC++, SP--


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

    DATA.data_out.connect(PCh.data_in) ;
    PCh_e.connect(PCh.enable) ;
    PCh_s.connect(PCh.set) ;
    PCh.data_out.connect(ADDRh.data_in) ;

    DATA.data_out.connect(PCl.data_in) ;    
    PCl_e.connect(PCl.enable) ;
    PCl_s.connect(PCl.set) ;
    PCl.data_out.connect(ADDRl.data_in) ;

    SPh_v.connect(SPh.data_in) ;
    SPh_v = 0x01 ;
    SPh_e.connect(SPh.enable) ;
    SPh.data_out.connect(ADDRh.data_in) ;

    DATA.data_out.connect(SP.data_in) ;
    SP_e.connect(SP.enable) ;
    SP_s.connect(SP.set) ;
    SP.data_out.connect(ADDRl.data_in) ;

    DATA.data_out.connect(ACC.data_in) ;
    ACC_e.connect(ACC.enable) ;
    ACC_s.connect(ACC.set) ;
    ACC.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(A.data_in) ;
    A_e.connect(A.enable) ;
    A_s.connect(A.set) ;
    A_e = 1 ;

    DATA.data_out.connect(B.data_in) ;
    B_e.connect(B.enable) ;
    B_s.connect(B.set) ;
    B_e = 1 ;   

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

    STATUS_b_in.connect(STATUS.b_in) ;
    STATUS_nz_set.connect(STATUS.nz_set) ;
    STATUS_v_set.connect(STATUS.v_set) ;
    STATUS_c_set.connect(STATUS.c_set) ;
    STATUS_alu_c_set.connect(STATUS.alu_c_set) ;
    STATUS_alu_c_from_C.connect(STATUS.alu_c_from_C) ;
    STATUS_data_enable.connect(STATUS.data_enable) ;
    STATUS_src_data.connect(STATUS.src_data) ;
    DATA.data_out.connect(STATUS.data_in) ;
    STATUS.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(INST.data_in) ;
    INST_s.connect(INST.set) ;
    INST_e.connect(INST.enable) ;
    INST_e = 1 ;
}

void setV(){
    STATUS_v_set = 1 ; STATUS_v_set = 0 ; 
}

void setC(){
    STATUS_c_set = 1 ; STATUS_c_set = 0 ; 
}

void setalucfromC(){
    STATUS_alu_c_from_C = 1 ; STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; STATUS_alu_c_from_C = 0 ;  
}

void setNZ(){
    STATUS_nz_set = 1 ; STATUS_nz_set = 0 ;  
}

/*
uint8_t pull8() {
    SP = SP + 1 ;
    return RAM._mem[SPh][SP] ;
}
*/


#include "addrmodes.h"
#include "ops.h"


#define tick(op)     for (int s = 0 ; s < 16 ; s++){ for (int c = 0 ; c < 4 ; c++){ if (! op(s << 4 | c)){ return ; } ; } }


//instruction handler functions
static void adc() { // 2 cycles
    tick(adc) ;
}

static void and_() { // 3 cycles
    tick(and_) ;
}

static void asl() { // 2 cycles
    tick(asl) ;
}

static void bcc(){ // 2 cycle
    tick(bcc) ;
}

static void bcs() { // 2 cycle
    tick(bcs) ;
}

static void beq(){ // 2 cycle
    tick(beq) ;
}

static void bit() { // 2 cycles
    tick(bit) ;
}

static void bmi() { // 2 cycle
    tick(bmi) ;
}

static void bne(){ // 2 cycle
    tick(bne) ;
}

static void bpl() { // 2 cycle
    tick(bpl) ;
}

static void brk() {
    tick(brk) ;
}

static void bvc() { // 2 cycle
    tick(bvc) ;
}

static void bvs() { // 2 cycle
    tick(bvs) ;
}

static void clc() { // 2 cycle
    tick(clc) ;
}

static void cld() {
    tick(cld) ;
}

static void cli() { // 1 cycle
    tick(cli) ;
}

static void clv() { // 2 cycle
    tick(clv) ;
}

static void cmp() { // 2 cycles
    tick(cmp) ;
}

static void cpx() { // 2 cycles
    tick(cpx) ;
}

static void cpy() { // 2 cycles
    tick(cpy) ;
}

static void dec() { // 1 cycles
    tick(dec) ;
}

static void dex() { // 2 cycles
    tick(dex) ;
}

static void dey() { // 2 cycles
    tick(dey) ;
}

static void eor() {
    tick(eor) ;
}

static void inc() {
    tick(inc) ;
}

static void inx() {
    tick(inx) ;
}

static void iny() {
    tick(iny) ;
}

static void jmp() {
    tick(jmp) ;
}

static void jsr() { // 9 cycles
    tick(jsr) ;
}

static void lda() {
    tick(lda) ; 
}

static void ldx() {
    tick(ldx) ; 
}

static void ldy() {
    tick(ldy) ;
}

static void lsr() {
    tick(lsr) ;
}

static void nop() {
    tick(nop) ;
}

static void ora() {
    tick(ora) ;
}

static void pha() {
    tick(pha) ;
}

static void php() {
    tick(php) ;
}

static void pla() { // 4 cycles
    tick(pla) ;
}

static void plp() {
    tick(plp) ;
}

static void rol() {
    STATUS_alu_c_from_C = 1 ; 
        STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; 
            STATUS_alu_c_from_C = 0 ; 
    if ((INST & 0xF) == 0xA){
        ALU_op = ALU_ROL ; ALU_e = 1 ; 
            ACC_s = 1 ; ACC_s = 0 ; setC() ; setNZ() ; 
                ALU_e = 0 ; // ACC = ALU ;
    }
    else {
        ALU_op = ALU_ROL ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; 
            RAM_s = 1 ; RAM_s = 0 ; setC() ; setNZ() ; 
                ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
    }
}

static void ror() {
    STATUS_alu_c_from_C = 1 ; 
        STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; 
            STATUS_alu_c_from_C = 0 ; 
    if ((INST & 0xF) == 0xA){
        ALU_op = ALU_ROR ; ALU_e = 1 ; 
            ACC_s = 1 ; ACC_s = 0 ; setC() ; setNZ() ; 
                ALU_e = 0 ; // ACC = ALU ;
    }
    else {
        ALU_op = ALU_ROR ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; 
            RAM_s = 1 ; RAM_s = 0 ; setC() ; setNZ() ; 
                ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
    }
}

static void rti() {
    SP_e = 1 ; Al2D_e = 1 ; 
        B_s = 1 ; B_s = 0 ; 
            Al2D_e = 0 ; SP_e = 0 ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
        SP_s = 1 ; SP_s = 0 ;
            ALU_e = 0 ;  
    SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; STATUS_src_data = 1 ; 
        STATUS_nz_set = 1 ; STATUS_v_set = 1 ; STATUS_c_set = 1 ;
        STATUS_nz_set = 0 ; STATUS_v_set = 0 ; STATUS_c_set = 0 ; 
            STATUS_src_data = 0 ; SPh_e = 0 ; SP_e = 0 ; RAM_e = 0 ; 

    SP_e = 1 ; Al2D_e = 1 ; 
        B_s = 1 ; B_s = 0 ; 
            Al2D_e = 0 ; SP_e = 0 ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
        SP_s = 1 ; SP_s = 0 ;
            ALU_e = 0 ;
    SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; 
        PCl_s = 1 ; PCl_s = 0 ; 
            RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ;                       
    SP_e = 1 ; Al2D_e = 1 ; 
        B_s = 1 ; B_s = 0 ; 
            Al2D_e = 0 ; SP_e = 0 ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
        SP_s = 1 ; SP_s = 0 ;
            ALU_e = 0 ;
    SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; 
        PCh_s = 1 ; PCh_s = 0 ; 
            RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ;
}

static void rts() {
    SP_e = 1 ; Al2D_e = 1 ; 
        B_s = 1 ; B_s = 0 ; 
            Al2D_e = 0 ; SP_e = 0 ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
        SP_s = 1 ; SP_s = 0 ;
            ALU_e = 0 ;
    SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; 
        PCl_s = 1 ; PCl_s = 0 ; 
            RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ;
    SP_e = 1 ; Al2D_e = 1 ; 
        B_s = 1 ; B_s = 0 ; 
            Al2D_e = 0 ; SP_e = 0 ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
        SP_s = 1 ; SP_s = 0 ;
            ALU_e = 0 ;
    SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; 
        PCh_s = 1 ; PCh_s = 0 ; 
            RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ;
                incPC() ;
}

static void sbc() {
    tick(sbc) ;
}

static void sec() {
    tick(sec) ;
}

static void sed() {
    tick(sed) ;
}

static void sei() {
    tick(sei) ;
}

static void sta() {
    tick(sta) ;
}

static void stx() {
    tick(stx) ;
}

static void sty() {
    tick(sty) ;
}

static void tax() {
    tick(tax) ;
}

static void tay() {
    tick(tay) ;
}

static void tsx() {
    tick(tsx) ;
}

static void txa() {
    tick(txa) ;
}

static void txs() {
    tick(txs) ;
}

static void tya() {
    tick(tya) ;
}


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

static void (*optable[256])() = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |      */
/* 0 */      brk,  ora,  nop,  slo,  nop,  ora,  asl,  slo,  php,  ora,  asl,  nop,  nop,  ora,  asl,  slo, /* 0 */
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


/*
void nmi6502() {
    push8(PCh) ;
    push8(PCl) ;
    STATUS_data_enable = 1 ;
    push8(STATUS.data_out) ;
    STATUS_data_enable = 0 ;
    setI(1) ; 
    PCl = MEM_read(0xFFFA) ;
    PCh = MEM_read(0xFFFB) ;
}

void irq6502() {
    push8(PCh) ;
    push8(PCl) ;
    STATUS_data_enable = 1 ;
    push8(STATUS.data_out) ;
    STATUS_data_enable = 0 ;
    setI(1) ;
    PCl = MEM_read(0xFFFE) ;
    PCh = MEM_read(0xFFFF) ;
}
*/


void do_inst(){
    uint8_t addr_start = 0, op_start = 0 ;
    bool fetch_done = false, addr_done = false, op_done = false ;
    for (int step = 0 ; step < 16 ; step++){
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
                (*optable[INST])() ;
                return ;
            }
        }
    }
}


int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Usage: %s SUCCESS_ADDR_IN_HEX\n", argv[0]) ;
        exit(1) ;
    }

    uint16_t SUCCESS_ADDR = (uint16_t)strtol(argv[1], NULL, 16) ;
    printf("Success address is 0x%X\n", SUCCESS_ADDR) ;

    FILE *file = fopen("6502_functional_test.bin", "rb") ; 
    uint8_t mem[0x10000] ;
    int nb = fread(mem, 0x10000, 1, file) ;
    for (int i = 0 ; i < 0x10000 ; i++){
        RAM._mem[i >> 8][i & 0xFF] = mem[i] ;
    }
    fclose(file) ;

    init6502() ;
    // PCl = MEM_read(0xFFFC) ;
    // PCh = MEM_read(0xFFFD) ;
    PCh = 0x00 ;
    PCl = 0x00 ;
    SP = 0x00 ;

    while (1) {
        if ((PCh << 8 | PCl) == SUCCESS_ADDR){
            printf("SUCCESS!\n") ;
            exit(0) ;
        }

        do_inst() ;
    }
}