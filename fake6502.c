#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "circuit.h"
#include "reg.h"
#include "ALU.h"

#include "DATA.h"
#include "STATUS.h"

DATA DATA ;
STATUS STATUS(&DATA) ;

uint16_t BUS_ADDR ;

uint8_t MEM[0x10000] ;

void MEM_write(){
    MEM[BUS_ADDR] = DATA.data.v() ;
}

void MEM_read(){
    DATA.data.v(MEM[BUS_ADDR]) ;
}


struct ADDR {
    uint8_t MARH, MARL ;
    uint16_t EA ;
    uint8_t SP ;
    uint16_t PC ;
} ADDR ;


//uint8_t INST ;


uint8_t read6502(uint16_t address){
    if (address == 0x336D){
        printf("SUCCESS!\n") ;
        exit(0) ;
    }
    /* if (address == 0x338e){
        printf("ad1:%d, ad2:%d\n", MEM[0x000D], MEM[0x000E]) ;
        if ((MEM[0x000D] == 255)&&(MEM[0x000E] == 255)){
            print = 1 ;
        }
    } */
    ADDR.MARH = address >> 8 ;
    ADDR.MARL = address & 0xFF ;

    uint8_t value = MEM[(ADDR.MARH << 8) | ADDR.MARL] ;
    /* if (print){
        if (address >= 0x0400){
            printf("MEM[%04X] => %02X\n", address, value) ;
        }
    } */

    return value ;
}


reg<8> ACC ;
output<1> ACC_s, ACC_e ;
reg<8> A, B, ADD ;
reg<1> CI, CO ;
output<1> A_s, A_e, B_s, B_e, CI_s, CI_e, ADD_s, ADD_e, CO_s, CO_e ;
reg<8> X, Y ;
output<1> X_s, X_e, Y_s, Y_e ;

ALU ALU ;
output<4> ALU_op ;

reg<8> INST ;
output<1> INST_s, INST_e ;


void init6502(){
    ACC_e.connect(ACC.enable) ;
    ACC_s.connect(ACC.set) ;

    A_e.connect(A.enable) ;
    A_s.connect(A.set) ;
    A_e = 1 ;
    B_e.connect(B.enable) ;
    B_s.connect(B.set) ;
    B_e = 1 ;   
    CI_e.connect(CI.enable) ;
    CI_s.connect(CI.set) ;
    CI_e = 1 ;
    ADD_e.connect(ADD.enable) ;
    ADD_s.connect(ADD.set) ;
    CO_e.connect(CO.enable) ;
    CO_s.connect(CO.set) ;

    X_e.connect(X.enable) ;
    X_s.connect(X.set) ;
    Y_e.connect(Y.enable) ;
    Y_s.connect(Y.set) ;

    A.data_out.connect(ALU.a) ;
    B.data_out.connect(ALU.b) ;
    CI.data_out.connect(ALU.c_in) ;    
    ALU_op.connect(ALU.op) ;
    ALU.res.connect(ADD.data_in) ;

    INST_e.connect(INST.enable) ;
    INST_s.connect(INST.set) ;
}

void setV(){
    STATUS.addr.bit(STATUS_ADDR_V)->v(ALU.v ? 1 : 0) ;
    STATUS.addr.bit(STATUS_ADDR_SET_V)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_V)->v(0) ;
}

void setC(){
    STATUS.addr.bit(STATUS_ADDR_C)->v(ALU.c ? 1 : 0) ;
    STATUS.addr.bit(STATUS_ADDR_SET_C)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_C)->v(0) ;
}

void setNZ(){
    STATUS.addr.bit(STATUS_ADDR_Z)->v(ALU.z) ;
    STATUS.addr.bit(STATUS_ADDR_SET_Z)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_Z)->v(0) ;
    STATUS.addr.bit(STATUS_ADDR_N)->v(ALU.n) ;
    STATUS.addr.bit(STATUS_ADDR_SET_N)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_N)->v(0) ;
}


void push8(uint8_t data) {
    MEM[0x0100 | ADDR.SP] = data ;
    ADDR.SP-- ;
}


uint8_t pull8() {
    ADDR.SP++ ;
    return MEM[0x0100 | ADDR.SP] ;
}


//addressing mode functions, calculates effective addresses
static void imp() { //implied
}

static void acc() { //accumulator
}

static void imm() { //immediate, 1 cycle
    BUS_ADDR = ADDR.PC ; MEM_read() ; B = DATA.data.v() ; ADDR.PC++ ;
}

static void zp() { //zero-page, 2 cycles
    BUS_ADDR = ADDR.PC ; MEM_read() ; ADDR.EA = DATA.data.v() ;
    BUS_ADDR = ADDR.EA ; MEM_read() ; B = DATA.data.v() ; ADDR.PC++ ;
}

static void zpx() { //zero-page,X, 5 cycles
    A = X ;
    BUS_ADDR = ADDR.PC ; MEM_read() ; B = DATA.data.v() ;
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA = ADD ; 
    BUS_ADDR = ADDR.EA ; MEM_read() ; B = DATA.data.v() ; ADDR.PC++ ;
}

static void zpy() { //zero-page,Y, 5 cycles
    A = Y ;
    BUS_ADDR = ADDR.PC ; MEM_read() ; B = DATA.data.v() ;
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA = ADD ; 
    BUS_ADDR = ADDR.EA ; MEM_read() ; B = DATA.data.v() ; ADDR.PC++ ;
}

static void rel() { //relative for branch ops (8-bit immediate value, sign-extended)
    BUS_ADDR = ADDR.PC ; MEM_read() ; ADDR.EA = DATA.data.v() ;
    // TODO: LOGIC
    if (ADDR.EA & 0x80) ADDR.EA |= 0xFF00 ;
    ADDR.PC++ ;

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
    BUS_ADDR = ADDR.PC ; MEM_read() ; ADDR.EA = DATA.data.v() ; ADDR.PC++ ;
    BUS_ADDR = ADDR.PC ; MEM_read() ; ADDR.EA |= DATA.data.v() << 8 ;
    BUS_ADDR = ADDR.EA ; MEM_read() ; B = DATA.data.v() ; ADDR.PC++ ;
}

static void absx() { //absolute,X, 10 cycles
    A = X ;
    BUS_ADDR = ADDR.PC ; MEM_read() ; B = DATA.data.v() ; ADDR.PC++ ;
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ; // first result is stored in ADD
    CI = ALU.c ; // this is ok since ALU_ADD does not use the CI

    A = 0 ;
    BUS_ADDR = ADDR.PC ; MEM_read() ; B = DATA.data.v() ; ADDR.PC++ ;
    ADDR.EA = ADD ;         // save first result before going on.
    ALU_op = ALU_ADC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA |= ADD << 8 ;

    BUS_ADDR = ADDR.EA ; MEM_read() ; B = DATA.data.v() ;
}

static void absy() { //absolute,Y,  10 cycles
    A = Y ;
    BUS_ADDR = ADDR.PC ; MEM_read() ; B = DATA.data.v() ; ADDR.PC++ ;
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ; // first result is stored in ADD
    CI = ALU.c ; // this is ok since ALU_ADD does not use the CI

    A = 0 ;
    BUS_ADDR = ADDR.PC ; MEM_read() ; B = DATA.data.v() ; ADDR.PC++ ;
    ADDR.EA = ADD ;         // save first result before going on.
    ALU_op = ALU_ADC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA |= ADD << 8 ;

    BUS_ADDR = ADDR.EA ; MEM_read() ; B = DATA.data.v() ;
}

static void ind() { //indirect, 13 cycles
    ADDR.EA = read6502(ADDR.PC) ; ADDR.PC++ ;
    ADDR.EA |= read6502(ADDR.PC) << 8 ; ADDR.PC++ ;

    A = read6502(ADDR.EA) ;
    B = ADDR.EA & 0xFF ;
    ALU_op = ALU_INC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA |= ADD ;
    B = read6502(ADDR.EA) ;
    // We need to bring A to ADDR.EAl and B to ADDR.EAh
    ALU_op = ALU_PASS ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA = ADD << 8 ;
    B = 0 ;
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA |= ADD ;

    B = read6502(ADDR.EA) ;
}

static void indx() { // (indirect,X), 9 cycles
    B = read6502(ADDR.PC++) ;
    A = X ; 
    ALU_op = ALU_ADD ; ADD_s = 1 ; ADD_s = 0 ;
    B = ADD ;
    ALU_op = ALU_INC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA = read6502(ADD) << 8 ;
    ALU_op = ALU_PASS ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA |= read6502(ADD) ;
    B = read6502(ADDR.EA) ;
}

static void indy() { // (indirect),Y
    B = read6502(ADDR.PC) ; ADDR.PC++ ;
    ALU_op = ALU_INC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA = read6502(ADD) << 8 ;
    ALU_op = ALU_PASS ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.EA |= read6502(ADD) ;
    // TODO
    ADDR.EA += Y ;
    B = read6502(ADDR.EA) ;
}

static void putvalue(uint16_t data) {
    BUS_ADDR = ADDR.EA ;
    DATA.data.v(data) ;
    MEM_write() ;
}


//instruction handler functions
static void adc() { // 3 cycles
    CI = STATUS.data.bit(STATUS_DATA_C)->v() ; A = ACC ; 
    ALU_op = ALU_ADC ; ADD_s = 1 ; ADD_s = 0 ;
    ACC = ADD ; setC() ; setV() ; setNZ() ;
}

static void and_() { // 3 cycles
    A = ACC ;
    ALU_op = ALU_AND ; ADD_s = 1 ; ADD_s = 0 ;
    ACC = ADD ; setNZ() ;
}

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

static void bcc() { // 1 cycle
    if (! STATUS.data.bit(STATUS_DATA_C)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void bcs() { // 1 cycle
    if (STATUS.data.bit(STATUS_DATA_C)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void beq() { // 1 cycle
    if (STATUS.data.bit(STATUS_DATA_Z)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void bit() { // 3 cycles
    A = ACC ;
    ALU_op = ALU_BIT ;
    setV() ; setNZ() ;
}

static void bmi() { // 1 cycle
    if (STATUS.data.bit(STATUS_DATA_N)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void bne() { // 1 cycle
    if (! STATUS.data.bit(STATUS_DATA_Z)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void bpl() { // 1 cycle
    if (! STATUS.data.bit(STATUS_DATA_N)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void brk() {
    ADDR.PC++;
    push8(ADDR.PC >> 8) ;
    push8(ADDR.PC & 0xFF) ;

    STATUS.B.v(1) ; STATUS.enable.v(1) ;
    push8(DATA.data.v()) ; //push CPU status to stack
    STATUS.enable.v(0) ; STATUS.B.v(0) ;

    STATUS.addr.bit(STATUS_ADDR_I)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_I)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_I)->v(0) ;
    ADDR.PC = read6502(0xFFFE) | read6502(0xFFFF) << 8 ;
}

static void bvc() { // 1 cycle
    if (! STATUS.data.bit(STATUS_DATA_V)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void bvs() { // 1 cycle
    if (STATUS.data.bit(STATUS_DATA_V)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void clc() { // 1 cycle
    STATUS.addr.bit(STATUS_ADDR_C)->v(0) ;
    STATUS.addr.bit(STATUS_ADDR_SET_C)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_C)->v(0) ;
}

static void cld() { // 1 cycle
    STATUS.addr.bit(STATUS_ADDR_D)->v(0) ;
    STATUS.addr.bit(STATUS_ADDR_SET_D)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_D)->v(0) ;
}

static void cli() { // 1 cycle
    STATUS.addr.bit(STATUS_ADDR_I)->v(0) ;
    STATUS.addr.bit(STATUS_ADDR_SET_I)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_I)->v(0) ;
}

static void clv() { // 1 cycle
    STATUS.addr.bit(STATUS_ADDR_V)->v(0) ;
    STATUS.addr.bit(STATUS_ADDR_SET_V)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_V)->v(0) ;
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

static void jsr() { // 11 cycles
    A = ADDR.PC >> 8 ;
    B = ADDR.PC & 0xFF ;
    ALU_op = ALU_DEC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.PC = ADD ;
    CI = ALU.c ; // ok because ALU_DEC ignores CI
    B = 0 ;
    ALU_op = ALU_SBC ; ADD_s = 1 ; ADD_s = 0 ;
    ADDR.PC |= ADD << 8 ;

    push8(ADDR.PC >> 8) ;
    push8(ADDR.PC & 0xFF) ;
    ADDR.PC = ADDR.EA ;
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
    STATUS.B.v(1) ; STATUS.enable.v(1) ;
    push8(DATA.data.v()) ; //push CPU status to stack
    STATUS.enable.v(0) ; STATUS.B.v(0) ;
}

static void pla() {
    B = pull8() ;
    ALU_op = ALU_PASS ; ADD_s = 1 ; ADD_s = 0 ;
    ACC = ADD ; setNZ() ;
}

static void plp() {
    uint8_t status = pull8() ;
    DATA.data.v(status) ;
    STATUS.fromDATA.v(1) ;
    STATUS.fromDATA.v(0) ;
}

static void rol() {
    CI = STATUS.data.bit(STATUS_DATA_C)->v() ;
    ALU_op = ALU_ROL ; ADD_s = 1 ; ADD_s = 0 ;
    if ((INST & 0xF) == 0xA)
        ACC = ADD ;
    else
        putvalue(ADD) ;
    setC() ; setNZ() ;
}

static void ror() {
    CI = STATUS.data.bit(STATUS_DATA_C)->v() ;
    ALU_op = ALU_ROR ; ADD_s = 1 ; ADD_s = 0 ;
    if ((INST & 0xF) == 0xA)
        ACC = ADD ;
    else
        putvalue(ADD) ;
    setC() ; setNZ() ;
}

static void rti() {
    uint8_t status = pull8() ;
    DATA.data.v(status) ;
    STATUS.fromDATA.v(1) ;
    STATUS.fromDATA.v(0) ;
    ADDR.PC = 0 | pull8() ;                 
    ADDR.PC = ADDR.PC | (pull8() << 8) ; 
}

static void rts() {
    ADDR.PC = 0 | pull8() ;                 
    ADDR.PC = ADDR.PC | (pull8() << 8) ;
    ADDR.PC++ ;
}

static void sbc() {
    CI = STATUS.data.bit(STATUS_DATA_C)->v() ;
    A = ACC ; 
    ALU_op = ALU_SBC ; ADD_s = 1 ; ADD_s = 0 ;
    ACC = ADD ; setC() ; setV() ; setNZ() ;
}

static void sec() {
    STATUS.addr.bit(STATUS_ADDR_C)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_C)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_C)->v(0) ;
}

static void sed() {
    STATUS.addr.bit(STATUS_ADDR_D)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_D)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_D)->v(0) ;
}

static void sei() {
    STATUS.addr.bit(STATUS_ADDR_I)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_I)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_I)->v(0) ;
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
    B = ADDR.SP ;
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
    ADDR.SP = ADD ; 
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
    ADDR.PC = read6502(0xFFFC) | read6502(0xFFFD) << 8 ;
    ADDR.SP = 0xFD ;
}

void nmi6502() {
    push8(ADDR.PC >> 8) ;
    push8(ADDR.PC & 0xFF) ;
    STATUS.enable.v(1) ;
    push8(DATA.data.v()) ;
    STATUS.enable.v(0) ;
    STATUS.addr.bit(STATUS_ADDR_I)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_I)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_I)->v(0) ;
    ADDR.PC = read6502(0xFFFA) | read6502(0xFFFB) << 8 ;
}

void irq6502() {
    push8(ADDR.PC >> 8) ;
    push8(ADDR.PC & 0xFF) ;
    STATUS.enable.v(1) ;
    push8(DATA.data.v()) ;
    STATUS.enable.v(0) ;
    STATUS.addr.bit(STATUS_ADDR_I)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_I)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_I)->v(0) ;
    ADDR.PC = read6502(0xFFFE) | read6502(0xFFFF) << 8 ;
}

uint8_t callexternal = 0;
void (*loopexternal)();


void step6502() { 
    INST = read6502(ADDR.PC) ; ADDR.PC++ ; // 1 cycle

    (*addrtable[INST])();
    (*optable[INST])();
}

void exec6502() {
    while (1) {
        step6502() ;
    }
}

int main(){
    FILE *file = fopen("6502_functional_test.bin", "rb") ; 
    int nb = fread(MEM, 0x10000, 1, file) ;
    fclose(file) ; 

    init6502() ;
    reset6502() ;
    ADDR.PC = 0x0400 ;

    exec6502() ;
}