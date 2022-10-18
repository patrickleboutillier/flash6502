#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "circuit.h"
#include "reg.h"
#include "bus.h"

#include "ALU.h"
#include "STATUS.h"


uint8_t MEM[0x10000] ;
uint16_t SUCCESS_ADDR = 0 ;

uint8_t MEM_read(uint16_t address, bool check_success = true){
    if ((check_success)&&(address == SUCCESS_ADDR)){
        printf("SUCCESS!\n") ;
        exit(0) ;
    }

    return MEM[address] ;
}

void MEM_write(uint16_t addr, uint8_t data){
    MEM[addr] = data ;
}


struct ADDR {
    uint16_t EA ;
    uint16_t PC ;
} ADDR ;


bus<8> DATA ;

reg<8> EAh, EAl, PCh, PCl, SPh, SP ;
output<1> EAh_s, EAh_e, EAl_s, EAl_e, PCh_s, PCh_e, PCl_s, PCl_e, SPh_s, SPh_e, SP_s, SP_e ;

reg<8> ACC ;
output<1> ACC_s, ACC_e ;
reg<8> A, B, ADD ;
reg<1> CI, CO ;
output<1> A_s, A_e, B_s, B_e, CI_s, CI_e, ADD_s, ADD_e, CO_s, CO_e ;
reg<8> X, Y ;
output<1> X_s, X_e, Y_s, Y_e ;

ALU ALU ;
output<4> ALU_op ;

STATUS STATUS ;
output<1> STATUS_i_in, STATUS_b_in ;
output<1> STATUS_nz_set, STATUS_v_set, STATUS_i_set, STATUS_c_set ;
output<1> STATUS_data_enable, STATUS_src_data ;
output<8> STATUS_data_in ;

reg<8> INST ;
output<1> INST_s, INST_e ;


void init6502(){
    EAh_e.connect(EAh.enable) ;
    EAh_s.connect(EAh.set) ;

    EAl_e.connect(EAl.enable) ;
    EAl_s.connect(EAl.set) ;

    PCh_e.connect(PCh.enable) ;
    PCh_s.connect(PCh.set) ;
    
    PCl_e.connect(PCl.enable) ;
    PCl_s.connect(PCl.set) ;

    SPh_e.connect(SPh.enable) ;
    SPh_s.connect(SPh.set) ;
    SPh = 0x01 ;
    
    SP_e.connect(SP.enable) ;
    SP_s.connect(SP.set) ;

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

    CI_e.connect(CI.enable) ;
    CI_s.connect(CI.set) ;
    CI_e = 1 ;

    ADD_e.connect(ADD.enable) ;
    ADD_s.connect(ADD.set) ;
    ADD.data_out.connect(DATA.data_in) ;

    CO_e.connect(CO.enable) ;
    CO_s.connect(CO.set) ;

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
    CI.data_out.connect(ALU.c_in) ;    
    ALU_op.connect(ALU.op) ;
    ALU.res.connect(ADD.data_in) ;

    ALU.n.connect(STATUS.n_in) ;
    ALU.v.connect(STATUS.v_in) ;
    ALU.z.connect(STATUS.z_in) ;
    ALU.c.connect(STATUS.c_in) ;
    STATUS_i_in.connect(STATUS.i_in) ;
    STATUS_b_in.connect(STATUS.b_in) ;
    STATUS_nz_set.connect(STATUS.nz_set) ;
    STATUS_v_set.connect(STATUS.v_set) ;
    STATUS_i_set.connect(STATUS.i_set) ;
    STATUS_c_set.connect(STATUS.c_set) ;
    STATUS_data_enable.connect(STATUS.data_enable) ;
    STATUS_src_data.connect(STATUS.src_data) ;
    STATUS_data_in.connect(STATUS.data_in) ; 
    STATUS.data_out.connect(DATA.data_in) ;

    INST_e.connect(INST.enable) ;
    INST_s.connect(INST.set) ;
}

void setV(){
    STATUS_v_set = 1 ; STATUS_v_set = 0 ; 
}

void setC(){
    STATUS_c_set = 1 ; STATUS_c_set = 0 ; 
}

void setNZ(){
    STATUS_nz_set = 1 ; STATUS_nz_set = 0 ;  
}

void setI(uint8_t i){
    STATUS_i_in = i ; 
    STATUS_i_set = 1 ; STATUS_i_set = 0 ;
    STATUS_i_in = 0 ; 
}

void push8(uint8_t data) {
    MEM[SPh << 8 | SP] = data ;
    SP = SP - 1 ;
}


uint8_t pull8() {
    SP = SP + 1 ;
    return MEM[SPh << 8 | SP] ;
}


//addressing mode functions, calculates effective addresses
static void imp() { //implied
}

static void acc() { //accumulator
}

static void imm() { //immediate, 1 cycle
    B = MEM_read(ADDR.PC) ; ADDR.PC++ ;
}

static void zp() { //zero-page, 2 cycles
    ADDR.EA = MEM_read(ADDR.PC) ;
    B = MEM_read(ADDR.EA) ; ADDR.PC++ ;
}

static void zpx() { //zero-page,X, 5 cycles
    A = X ;
    B = MEM_read(ADDR.PC) ;
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA = ADD ; 
    B = MEM_read(ADDR.EA) ; ADDR.PC++ ;
}

static void zpy() { //zero-page,Y, 5 cycles
    A = Y ;
    B = MEM_read(ADDR.PC) ;
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA = ADD ; 
    B = MEM_read(ADDR.EA) ; ADDR.PC++ ;
}

static void rel() { //relative for branch ops (8-bit immediate value, sign-extended)
    ADDR.EA = MEM_read(ADDR.PC) ; ADDR.PC++ ;
    // TODO: LOGIC
    if (ADDR.EA & 0x80) ADDR.EA |= 0xFF00 ;

    A = ADDR.EA & 0xFF ;
    B = ADDR.PC & 0xFF ;
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ;
    CI = ALU.c ; // Ok because ALU_ADD currently in use.
    A = ADDR.EA >> 8 ;
    B = ADDR.PC >> 8 ;
    ADDR.EA = ADD ;
    ALU_op = ALU_ADC ; ADD_s = 1 ; ADD_s = 0 ;

    ADDR.EA |= ADD << 8 ;
}

static void abso() { //absolute, 3 cycles
    ADDR.EA = MEM_read(ADDR.PC) ; ADDR.PC++ ;
    ADDR.EA |= MEM_read(ADDR.PC) << 8 ; ADDR.PC++ ;
    B = MEM_read(ADDR.EA) ;
}

static void absx() { //absolute,X, 10 cycles
    A = X ;
    B = MEM_read(ADDR.PC) ; ADDR.PC++ ;
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ; // first result is stored in ADD
    CI = ALU.c ; // this is ok since ALU_ADD does not use the CI

    A = 0 ;
    B = MEM_read(ADDR.PC) ; ADDR.PC++ ;
    ADDR.EA = ADD ;         // save first result before going on.
    ALU_op = ALU_ADC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA |= ADD << 8 ;

    B = MEM_read(ADDR.EA) ;
}

static void absy() { //absolute,Y,  10 cycles
    A = Y ;
    B = MEM_read(ADDR.PC) ; ADDR.PC++ ;
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ; // first result is stored in ADD
    CI = ALU.c ; // this is ok since ALU_ADD does not use the CI

    A = 0 ;
    B = MEM_read(ADDR.PC) ; ADDR.PC++ ;
    ADDR.EA = ADD ;         // save first result before going on.
    ALU_op = ALU_ADC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA |= ADD << 8 ;

    B = MEM_read(ADDR.EA) ;
}

static void ind() { //indirect, 12 cycles
    // Load ADDR_EAl and B at the same time
    ADDR.EA = MEM_read(ADDR.PC) ; B = MEM_read(ADDR.PC) ; ADDR.PC++ ;
    ADDR.EA |= MEM_read(ADDR.PC) << 8 ; ADDR.PC++ ;

    A = MEM_read(ADDR.EA) ;
    ALU_op = ALU_INC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA |= ADD ;
    B = MEM_read(ADDR.EA) ;
    // We need to bring A to ADDR.EAl and B to ADDR.EAh
    ALU_op = ALU_PASS ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA = ADD << 8 ;
    B = 0 ; // could be eliminated if the ALU had a PASSA instruction.
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA |= ADD ;

    B = MEM_read(ADDR.EA) ;
}

static void indx() { // (indirect,X), 9 cycles
    B = MEM_read(ADDR.PC) ; ADDR.PC++ ;
    A = X ; 
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ;
    B = ADD ;
    ALU_op = ALU_INC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA = MEM_read(ADD) << 8 ;
    ALU_op = ALU_PASS ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA |= MEM_read(ADD) ;
    B = MEM_read(ADDR.EA) ;
}

static void indy() { // (indirect),Y, 12 cycles
    B = MEM_read(ADDR.PC) ; ADDR.PC++ ;
    A = Y ; ALU_op = ALU_INC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA = MEM_read(ADD) << 8 ;
    ALU_op = ALU_PASS ; ADD_s = 1 ; ADD_s = 0 ;
    B = MEM_read(ADD) ;
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ;
    CI = ALU.c ; ADDR.EA |= ADD ; 
    A = 0 ;
    B = ADDR.EA >> 8 ;
    ALU_op = ALU_ADC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA = ADD << 8 | ADDR.EA & 0xFF ;
    B = MEM_read(ADDR.EA) ;
}

static void putvalue(uint16_t data) {
    MEM_write(ADDR.EA, data) ;
}


//instruction handler functions
static void adc() { // 3 cycles
    CI = STATUS.C ; A = ACC ; 
    ALU_op = ALU_ADC ; ADD_s = 1 ; ADD_s = 0 ;
    ACC = ADD ; setC() ; setV() ; setNZ() ;
}

static void and_() { // 3 cycles
    A = ACC ;
    ALU_op = ALU_AND ; ADD_s = 1 ; ADD_s = 0 ;
    ACC = ADD ; setNZ() ;
}

// TODO: Use ALU_ASL to bring down to 3 cycles.
static void asl() { // 4 cycles
    A = ACC ;
    B = ACC ;
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ;
    if ((INST & 0xF) == 0xA)
        ACC = ADD ;
    else
        putvalue(ADD) ;
    setC() ; setNZ() ;
}

static void bcc(){ // 1 cycle
    if (! STATUS.C){
        ADDR.PC = ADDR.EA ;
    }
}

static void bcs() { // 1 cycle
    if (STATUS.C){
        ADDR.PC = ADDR.EA ;
    }
}

static void beq(){ // 1 cycle
    if (STATUS.Z){
        ADDR.PC = ADDR.EA ;
    }
}

static void bit() { // 3 cycles
    A = ACC ;
    ALU_op = ALU_BIT ;
    setV() ; setNZ() ;
}

static void bmi() { // 1 cycle
    if (STATUS.N){
        ADDR.PC = ADDR.EA ;
    }
}

static void bne(){ // 1 cycle
    if (! STATUS.Z) {
        ADDR.PC = ADDR.EA ;
    }
}

static void bpl() { // 1 cycle
    if (! STATUS.N) {
        ADDR.PC = ADDR.EA ;
    }
}

static void brk() {
    ADDR.PC++;
    push8(ADDR.PC >> 8) ;
    push8(ADDR.PC & 0xFF) ;
    STATUS_b_in = 1 ;  STATUS_data_enable = 1 ;
    push8(STATUS.data_out) ; //push CPU status to stack
    STATUS_data_enable = 0 ; STATUS_b_in = 0 ;
    setI(1) ;
    ADDR.PC = MEM_read(0xFFFE) | MEM_read(0xFFFF) << 8 ;
}

static void bvc() { // 1 cycle
    if (! STATUS.V) {
        ADDR.PC = ADDR.EA ;
    }
}

static void bvs() { // 1 cycle
    if (STATUS.V) {
        ADDR.PC = ADDR.EA ;
    }
}

static void clc() { // 1 cycle
    B = 0 ;
    ALU_op = ALU_PASS ;
    setC() ;
}

static void cld() {
}

static void cli() { // 1 cycle
    setI(0) ;
}

static void clv() { // 1 cycle
    B = 0 ;
    ALU_op = ALU_PASS ;
    setV() ;
}

static void cmp() { // 3 cycles
    A = ACC ;
    ALU_op = ALU_CMP ;
    setC() ; setNZ() ; // don't save results
}

static void cpx() { // 3 cycles
    A = X ;
    ALU_op = ALU_CMP ;
    setC() ; setNZ() ; // don't save results
}

static void cpy() { // 3 cycles
    A = Y ;
    ALU_op = ALU_CMP ;
    setC() ; setNZ() ; // don't save results
}

static void dec() { // 2 cycles
    ALU_op = ALU_DEC ; ADD_s = 1 ; ADD_s = 0 ;
    putvalue(ADD) ; setNZ() ;
}

static void dex() { // 3 cycles
    B = X ;
    ALU_op = ALU_DEC ; ADD_s = 1 ; ADD_s = 0 ;
    X = ADD ; setNZ() ;
}

static void dey() { // 3 cycles
    B = Y ;
    ALU_op = ALU_DEC ; ADD_s = 1 ; ADD_s = 0 ;
    Y = ADD ; setNZ() ;
}

static void eor() {
    A = ACC ;
    ALU_op = ALU_EOR ; ADD_s = 1 ; ADD_s = 0 ;
    ACC = ADD ; setNZ() ;
}

static void inc() {
    ALU_op = ALU_INC ; ADD_s = 1 ; ADD_s = 0 ;
    putvalue(ADD) ; setNZ() ;
}

static void inx() {
    B = X ;
    ALU_op = ALU_INC ; ADD_s = 1 ; ADD_s = 0 ;
    X = ADD ; setNZ() ;
}

static void iny() {
    B = Y ;
    ALU_op = ALU_INC ; ADD_s = 1 ; ADD_s = 0 ;
    Y = ADD ; setNZ() ;
}

static void jmp() {
    ADDR.PC = ADDR.EA ;
}

static void jsr() { // 10 cycles
    A = ADDR.PC >> 8 ;
    B = ADDR.PC & 0xFF ;
    ALU_op = ALU_DEC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.PC = ADD ; CI = ALU.c ; // ok because ALU_DEC ignores CI
    B = 0 ;
    ALU_op = ALU_SBC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.PC |= ADD << 8 ;

    push8(ADDR.PC >> 8) ;
    // B = SP
    // ALU_op = ALU_DEC ; ADD_s = 1 ; ADD_s = 0 ;
    // SP = ADD ; B = ADD ;
    push8(ADDR.PC & 0xFF) ;
    // ALU_op = ALU_DEC ; ADD_s = 1 ; ADD_s = 0 ;
    // SP = ADD ; B = ADD ;
    ADDR.PC = ADDR.EA ; // Should be done in 2 insts through data bus
}

static void lda() {
    ALU_op = ALU_PASS ; ADD_s = 1 ; ADD_s = 0 ;
    ACC = ADD ; setNZ() ;
}

static void ldx() {
    ALU_op = ALU_PASS ; ADD_s = 1 ; ADD_s = 0 ;
    X = ADD ; setNZ() ;
}

static void ldy() {
    ALU_op = ALU_PASS ; ADD_s = 1 ; ADD_s = 0 ;
    Y = ADD ; setNZ() ;
}

static void lsr() {
    ALU_op = ALU_LSR ; ADD_s = 1 ; ADD_s = 0 ;
    if ((INST & 0xF) == 0xA)
        ACC = ADD ;
    else
        putvalue(ADD) ;
    setC() ; setNZ() ;
}

static void nop() {
}

static void ora() {
    A = ACC ;
    ALU_op = ALU_ORA ; ADD_s = 1 ; ADD_s = 0 ;
    ACC = ADD ; setNZ() ;
}

static void pha() {
    push8(ACC) ;
}

static void php() {
    STATUS_b_in = 1 ; STATUS_data_enable = 1 ;
    push8(STATUS.data_out) ; //push CPU status to stack
    STATUS_data_enable = 0 ; STATUS_b_in = 0 ;
}

static void pla() {
    B = pull8() ;
    ALU_op = ALU_PASS ; ADD_s = 1 ; ADD_s = 0 ;
    ACC = ADD ; setNZ() ;
}

static void plp() {
    STATUS_data_in = pull8() ;
    STATUS_src_data = 1 ;
    STATUS_nz_set = 1 ; STATUS_v_set = 1 ; STATUS_i_set = 1 ; STATUS_c_set = 1 ;
    STATUS_nz_set = 0 ; STATUS_v_set = 0 ; STATUS_i_set = 0 ; STATUS_c_set = 0 ;
    STATUS_src_data = 0 ;
}

static void rol() {
    CI = STATUS.C ;
    ALU_op = ALU_ROL ; ADD_s = 1 ; ADD_s = 0 ;
    if ((INST & 0xF) == 0xA)
        ACC = ADD ;
    else
        putvalue(ADD) ;
    setC() ; setNZ() ;
}

static void ror() {
    CI = STATUS.C ;
    ALU_op = ALU_ROR ; ADD_s = 1 ; ADD_s = 0 ;
    if ((INST & 0xF) == 0xA)
        ACC = ADD ;
    else
        putvalue(ADD) ;
    setC() ; setNZ() ;
}

static void rti() {
    STATUS_data_in = pull8() ;
    STATUS_src_data = 1 ;
    STATUS_nz_set = 1 ; STATUS_v_set = 1 ; STATUS_i_set = 1 ; STATUS_c_set = 1 ;
    STATUS_nz_set = 0 ; STATUS_v_set = 0 ; STATUS_i_set = 0 ; STATUS_c_set = 0 ;
    STATUS_src_data = 0 ;
    ADDR.PC = 0 | pull8() ;                 
    ADDR.PC = ADDR.PC | (pull8() << 8) ; 
}

static void rts() {
    ADDR.PC = 0 | pull8() ;                 
    ADDR.PC = ADDR.PC | (pull8() << 8) ;
    ADDR.PC++ ;
}

static void sbc() {
    CI = STATUS.C ; A = ACC ; 
    ALU_op = ALU_SBC ; ADD_s = 1 ; ADD_s = 0 ;
    ACC = ADD ; setC() ; setV() ; setNZ() ;
}

static void sec() {
    B = 0 ;
    ALU_op = ALU_INC ; ADD_s = 1 ; ADD_s = 0 ;
    B = ADD ;
    ALU_op = ALU_DEC ;
    setC() ;
}

static void sed() {
}

static void sei() {
    setI(1) ;
}

static void sta() {
    putvalue(ACC) ;
}

static void stx() {
    putvalue(X) ;
}

static void sty() {
    putvalue(Y) ;
}

static void tax() {
    B = ACC ;
    ALU_op = ALU_PASS ;
    ADD_s = 1 ; ADD_s = 0 ;
    X = ADD ; setNZ() ;
}

static void tay() {
    B = ACC ;
    ALU_op = ALU_PASS ;
    ADD_s = 1 ; ADD_s = 0 ;
    Y = ADD ; setNZ() ;
}

static void tsx() {
    B = SP ;
    ALU_op = ALU_PASS ;
    ADD_s = 1 ; ADD_s = 0 ;
    X = ADD ; setNZ() ;
}

static void txa() {
    B = X ;
    ALU_op = ALU_PASS ;
    ADD_s = 1 ; ADD_s = 0 ;
    ACC = ADD ; setNZ() ;
}

static void txs() {
    B = X ;
    ALU_op = ALU_PASS ;
    ADD_s = 1 ; ADD_s = 0 ;
    SP = ADD ; 
}

static void tya() {
    B = Y ;
    ALU_op = ALU_PASS ;
    ADD_s = 1 ; ADD_s = 0 ;
    ACC = ADD ; setNZ() ;
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


static void (*addrtable[256])() = {
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


void reset6502() {
    ADDR.PC = MEM_read(0xFFFC) | MEM_read(0xFFFD) << 8 ;
    SP = 0xFD ;
}

void nmi6502() {
    push8(ADDR.PC >> 8) ;
    push8(ADDR.PC & 0xFF) ;
    STATUS_data_enable = 1 ;
    push8(STATUS.data_out) ;
    STATUS_data_enable = 0 ;
    setI(1) ; 
    ADDR.PC = MEM_read(0xFFFA) | MEM_read(0xFFFB) << 8 ;
}

void irq6502() {
    push8(ADDR.PC >> 8) ;
    push8(ADDR.PC & 0xFF) ;
    STATUS_data_enable = 1 ;
    push8(STATUS.data_out) ;
    STATUS_data_enable = 0 ;
    setI(1) ;
    ADDR.PC = MEM_read(0xFFFE) | MEM_read(0xFFFF) << 8 ;
}

uint8_t callexternal = 0;
void (*loopexternal)();


void step6502() { 
    INST = MEM_read(ADDR.PC, true) ; ADDR.PC++ ; // 1 cycle

    (*addrtable[INST])();
    (*optable[INST])();
}

void exec6502() {
    while (1) {
        step6502() ;
    }
}

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Usage: %s SUCCESS_ADDR_IN_HEX\n", argv[0]) ;
        exit(1) ;
    }

    SUCCESS_ADDR = (uint16_t)strtol(argv[1], NULL, 16) ;
    printf("Success address is 0x%X\n", SUCCESS_ADDR) ;

    FILE *file = fopen("6502_functional_test.bin", "rb") ; 
    int nb = fread(MEM, 0x10000, 1, file) ;
    fclose(file) ; 

    init6502() ;
    reset6502() ;
    ADDR.PC = 0x0400 ;

    exec6502() ;
}