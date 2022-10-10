#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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


uint8_t INST ;


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


struct ALU {
    uint8_t A ;
    uint8_t B ;
    uint8_t CI ;
    uint8_t ADD ;
    uint8_t CO ;
    uint8_t ACC ;
    uint8_t X ;
    uint8_t Y ;
} ALU ;


void ALU_add(uint8_t setV){
    uint16_t sum = ALU.A + ALU.B + ALU.CI ;
    ALU.ADD = sum & 0XFF ;
    ALU.CO = sum >> 8 ;    
    
    if (setV){
        STATUS.addr.bit(STATUS_ADDR_V)->v(((sum ^ (uint16_t)ALU.A) & (sum ^ ALU.B) & 0x0080) ? 1 : 0) ;
        STATUS.addr.bit(STATUS_ADDR_SET_V)->v(1) ;
        STATUS.addr.bit(STATUS_ADDR_SET_V)->v(0) ;
    }
}

void ALU_setC(){
    STATUS.addr.bit(STATUS_ADDR_C)->v(ALU.CO ? 1 : 0) ;
    STATUS.addr.bit(STATUS_ADDR_SET_C)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_C)->v(0) ;
}

uint8_t ALU_setNZ(uint8_t v){
    DATA.data.v(v) ;
    STATUS.addr.bit(STATUS_ADDR_Z)->v(DATA.Z.v()) ;
    STATUS.addr.bit(STATUS_ADDR_SET_Z)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_Z)->v(0) ;
    STATUS.addr.bit(STATUS_ADDR_N)->v(DATA.N.v()) ;
    STATUS.addr.bit(STATUS_ADDR_SET_N)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_N)->v(0) ;
    return v ;
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

static void imm() { //immediate
    BUS_ADDR = ADDR.PC ; MEM_read() ; ALU.B = DATA.data.v() ;
    ADDR.PC++ ;
}

static void zp() { //zero-page
    BUS_ADDR = ADDR.PC ; MEM_read() ; ADDR.EA = DATA.data.v() ;
    BUS_ADDR = ADDR.EA ; MEM_read() ; ALU.B = DATA.data.v() ;
    ADDR.PC++ ;
}

static void zpx() { //zero-page,X
    ALU.CI = 0 ;
    ALU.A = ALU.X ;
    BUS_ADDR = ADDR.PC ; MEM_read() ; ALU.B = DATA.data.v() ;
    ALU_add(0) ;
    ADDR.EA = ALU.ADD ; 
    BUS_ADDR = ADDR.EA ; MEM_read() ; ALU.B = DATA.data.v() ;
    ADDR.PC++ ;
}

static void zpy() { //zero-page,Y
    ALU.CI = 0 ;
    ALU.A = ALU.Y ;
    BUS_ADDR = ADDR.PC ; MEM_read() ; ALU.B = DATA.data.v() ;
    ALU_add(0) ;
    ADDR.EA = ALU.ADD ; 
    BUS_ADDR = ADDR.EA ; MEM_read() ; ALU.B = DATA.data.v() ;
    ADDR.PC++ ;
}

static void rel() { //relative for branch ops (8-bit immediate value, sign-extended)
    BUS_ADDR = ADDR.PC ; MEM_read() ; ADDR.EA = DATA.data.v() ;
    if (ADDR.EA & 0x80) ADDR.EA |= 0xFF00 ;
    ADDR.PC++ ;
    ALU.CI = 0 ;
    ALU.A = ADDR.EA & 0xFF ;
    ALU.B = ADDR.PC & 0xFF ;
    ALU_add(0) ;
    ALU.CI = ALU.CO ;
    ALU.A = ADDR.EA >> 8 ;
    ALU.B = ADDR.PC >> 8 ;
    ADDR.EA = ALU.ADD ;
    ALU_add(0) ;
    ADDR.EA |= ALU.ADD << 8 ;
}

static void abso() { //absolute
    BUS_ADDR = ADDR.PC ; MEM_read() ; ADDR.EA = DATA.data.v() ;
    ADDR.PC++ ;
    BUS_ADDR = ADDR.PC ; MEM_read() ; ADDR.EA |= DATA.data.v() << 8 ;
    BUS_ADDR = ADDR.EA ; MEM_read() ; ALU.B = DATA.data.v() ;
    ADDR.PC++ ;
}

static void absx() { //absolute,X
    BUS_ADDR = ADDR.PC ; MEM_read() ; ADDR.EA = DATA.data.v() ;
    ADDR.PC++ ;
    BUS_ADDR = ADDR.PC ; MEM_read() ; ADDR.EA |= DATA.data.v() << 8 ;
    BUS_ADDR = ADDR.EA ; MEM_read() ; ALU.B = DATA.data.v() ;
    ADDR.PC++ ;
    ALU.CI = 0 ;
    ALU.A = ALU.X ;
    ALU.B = ADDR.EA & 0xFF ;
    ALU_add(0) ;  
    ALU.CI = ALU.CO ;
    ALU.A = 0 ;
    ALU.B = ADDR.EA >> 8 ;
    ADDR.EA = ALU.ADD ;
    ALU_add(0) ;
    ADDR.EA |= ALU.ADD << 8 ;
    BUS_ADDR = ADDR.EA ; MEM_read() ; ALU.B = DATA.data.v() ;
}

static void absy() { //absolute,Y
    BUS_ADDR = ADDR.PC ; MEM_read() ; ADDR.EA = DATA.data.v() ;
    ADDR.PC++ ;
    BUS_ADDR = ADDR.PC ; MEM_read() ; ADDR.EA |= DATA.data.v() << 8 ;
    BUS_ADDR = ADDR.EA ; MEM_read() ; ALU.B = DATA.data.v() ;
    ADDR.PC++ ;
    ALU.CI = 0 ;
    ALU.A = ALU.Y ;
    ALU.B = ADDR.EA & 0xFF ;
    ALU_add(0) ;  
    ALU.CI = ALU.CO ;
    ALU.A = 0 ;
    ALU.B = ADDR.EA >> 8 ;
    ADDR.EA = ALU.ADD ;
    ALU_add(0) ;
    ADDR.EA |= ALU.ADD << 8 ;
    BUS_ADDR = ADDR.EA ; MEM_read() ; ALU.B = DATA.data.v() ;
}

static void ind() { //indirect
    uint16_t eahelp, eahelp2;
    eahelp = 0  | (uint16_t)read6502(ADDR.PC) ;
    ADDR.PC++ ;
    eahelp = eahelp | ((uint16_t)read6502(ADDR.PC) << 8) ;
    ADDR.PC++ ;
    eahelp2 = (eahelp & 0xFF00) | ((eahelp + 1) & 0x00FF); //replicate 6502 page-boundary wraparound bug
    ADDR.EA = (uint16_t)read6502(eahelp) | ((uint16_t)read6502(eahelp2) << 8);
    ALU.B = read6502(ADDR.EA) ;
}

static void indx() { // (indirect,X)
    uint16_t eahelp;
    eahelp = (uint16_t)(((uint16_t)read6502(ADDR.PC++) + (uint16_t)ALU.X) & 0xFF); //zero-page wraparound for table pointer
    ADDR.EA = (uint16_t)read6502(eahelp & 0x00FF) | ((uint16_t)read6502((eahelp+1) & 0x00FF) << 8);
    ALU.B = read6502(ADDR.EA) ;
}

static void indy() { // (indirect),Y
    uint16_t eahelp, eahelp2, startpage;
    eahelp = (uint16_t)read6502(ADDR.PC++);
    eahelp2 = (eahelp & 0xFF00) | ((eahelp + 1) & 0x00FF); //zero-page wraparound
    ADDR.EA = (uint16_t)read6502(eahelp) | ((uint16_t)read6502(eahelp2) << 8);
    startpage = ADDR.EA & 0xFF00;
    ADDR.EA += (uint16_t)ALU.Y;
    ALU.B = read6502(ADDR.EA) ;

    //if (startpage != (ADDR.EA & 0xFF00)) { //one cycle penlty for page-crossing on some opcodes
    //    penaltyaddr = 1;
    //}
}


static void putvalue(uint16_t data) {
    BUS_ADDR = ADDR.EA ;
    DATA.data.v(data) ;
    MEM_write() ;
}


//instruction handler functions
static void adc() {
    ALU.CI = STATUS.data.bit(STATUS_DATA_C)->v() ;
    ALU.A = ALU.ACC ;
    ALU_add(1) ;  
    ALU_setC() ;
    ALU.ACC = ALU_setNZ(ALU.ADD) ;
}

static void and_() {
    ALU.A = ALU.ACC ;
    ALU.ADD = ALU.A & ALU.B ;   
    ALU.ACC = ALU_setNZ(ALU.ADD) ;
}

static void asl() {
    ALU.A = ALU.ACC ;
    uint16_t result = ALU.A << 1 ;
    ALU.ADD = result ;
    ALU.CO = result >> 8 ;
    ALU_setC() ;
   
    if ((INST & 0xF) == 0xA){
        ALU.ACC = ALU_setNZ(ALU.ADD) ;
    }
    else {
        putvalue(ALU_setNZ(ALU.ADD)) ;
    }
}

static void bcc() {
    if (! STATUS.data.bit(STATUS_DATA_C)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void bcs() {
    if (STATUS.data.bit(STATUS_DATA_C)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void beq() {
    if (STATUS.data.bit(STATUS_DATA_Z)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void bit() {
    ALU.A = ALU.ACC ;
    ALU.ADD = ALU.A & ALU.B ;
    STATUS.addr.bit(STATUS_ADDR_Z)->v(ALU.ADD ? 0 : 1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_Z)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_Z)->v(0) ;

    // TODO: How will we get this result on the data bus???
    DATA.data.v((STATUS.data.v() & 0x3F) | (ALU.B & 0xC0)) ;
    STATUS.fromDATA.v(1) ;
    STATUS.fromDATA.v(0) ;
}

static void bmi() {
    if (STATUS.data.bit(STATUS_DATA_N)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void bne() {
    if (! STATUS.data.bit(STATUS_DATA_Z)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void bpl() {
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
    ADDR.PC = (uint16_t)read6502(0xFFFE) | ((uint16_t)read6502(0xFFFF) << 8);
}

static void bvc() {
    if (! STATUS.data.bit(STATUS_DATA_V)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void bvs() {
    if (STATUS.data.bit(STATUS_DATA_V)->v()) {
        ADDR.PC = ADDR.EA ;
    }
}

static void clc() {
    STATUS.addr.bit(STATUS_ADDR_C)->v(0) ;
    STATUS.addr.bit(STATUS_ADDR_SET_C)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_C)->v(0) ;
}

static void cld() {
    STATUS.addr.bit(STATUS_ADDR_D)->v(0) ;
    STATUS.addr.bit(STATUS_ADDR_SET_D)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_D)->v(0) ;
}

static void cli() {
    STATUS.addr.bit(STATUS_ADDR_I)->v(0) ;
    STATUS.addr.bit(STATUS_ADDR_SET_I)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_I)->v(0) ;
}

static void clv() {
    STATUS.addr.bit(STATUS_ADDR_V)->v(0) ;
    STATUS.addr.bit(STATUS_ADDR_SET_V)->v(1) ;
    STATUS.addr.bit(STATUS_ADDR_SET_V)->v(0) ;
}

static void cmp() {
    ALU.CI = 1 ;
    ALU.A = ALU.ACC ;
    ALU.B = ALU.B ^ 0x00FF ; 
    ALU_add(0) ;
    ALU_setC() ;
    ALU_setNZ(ALU.ADD) ; // don't save results
}

static void cpx() {
    ALU.CI = 1 ;
    ALU.A = ALU.X ;
    ALU.B = ALU.B ^ 0x00FF ; 
    ALU_add(0) ;
    ALU_setC() ;
    ALU_setNZ(ALU.ADD) ; // don't save results
}

static void cpy() {
    ALU.CI = 1 ;
    ALU.A = ALU.Y ;
    ALU.B = ALU.B ^ 0x00FF ; 
    ALU_add(0) ;
    ALU_setC() ;
    ALU_setNZ(ALU.ADD) ; // don't save results
}

static void dec() {
    ALU.ADD = ALU.B - 1 ;
    putvalue(ALU_setNZ(ALU.ADD)) ;
}

static void dex() {
    ALU.B = ALU.X ;
    ALU.ADD = ALU.B - 1 ;
    ALU.X = ALU_setNZ(ALU.ADD) ;
}

static void dey() {
    ALU.B = ALU.Y ;
    ALU.ADD = ALU.B - 1 ;
    ALU.Y = ALU_setNZ(ALU.ADD) ;
}

static void eor() {
    ALU.A = ALU.ACC ;
    ALU.ADD = ALU.A ^ ALU.B ;
    ALU.ACC = ALU_setNZ(ALU.ADD) ;
}

static void inc() {
    ALU.ADD = ALU.B + 1 ;
    putvalue(ALU_setNZ(ALU.ADD));
}

static void inx() {
    ALU.B = ALU.X ;
    ALU.ADD = ALU.B + 1 ;
    ALU.X = ALU_setNZ(ALU.ADD) ;
}

static void iny() {
    ALU.B = ALU.Y ;
    ALU.ADD = ALU.B + 1 ;
    ALU.Y = ALU_setNZ(ALU.ADD) ;
}

static void jmp() {
    ADDR.PC = ADDR.EA ;
}

static void jsr() {
    ADDR.PC -= 1 ; 
    push8(ADDR.PC >> 8) ;
    push8(ADDR.PC & 0xFF) ;
    ADDR.PC = ADDR.EA ;
}

static void lda() {
    ALU.ADD = ALU.B ;
    ALU.ACC = ALU_setNZ(ALU.ADD) ;
}

static void ldx() {
    ALU.ADD = ALU.B ;
    ALU.X = ALU_setNZ(ALU.ADD) ;
}

static void ldy() {
    ALU.ADD = ALU.B ;
    ALU.Y = ALU_setNZ(ALU.ADD) ;
}

static void lsr() {
    ALU.ADD = ALU.B >> 1 ;
    ALU.CO = ALU.B & 1 ;
    ALU_setC() ;
    if ((INST & 0xF) == 0xA){
        ALU.ACC = ALU_setNZ(ALU.ADD) ;
    }
    else {
        putvalue(ALU_setNZ(ALU.ADD)) ;
    }
}

static void nop() {
}

static void ora() {
    ALU.A = ALU.ACC ;
    ALU.ADD = ALU.A | ALU.B ;
    ALU.ACC = ALU_setNZ(ALU.ADD) ;
}

static void pha() {
    push8(ALU.ACC);
}

static void php() {
    STATUS.B.v(1) ; STATUS.enable.v(1) ;
    push8(DATA.data.v()) ; //push CPU status to stack
    STATUS.enable.v(0) ; STATUS.B.v(0) ;
}

static void pla() {
    ALU.ACC = ALU_setNZ(pull8());
}

static void plp() {
    uint8_t status = pull8() ;
    DATA.data.v(status) ;
    STATUS.fromDATA.v(1) ;
    STATUS.fromDATA.v(0) ;
}

static void rol() {
    ALU.CI = STATUS.data.bit(STATUS_DATA_C)->v() ;
    uint16_t result = (ALU.B << 1) | ALU.CI ;
    ALU.ADD = result ;
    ALU.CO = result >> 8 ;
    ALU_setC() ;

    if ((INST & 0xF) == 0xA){
        ALU.ACC = ALU_setNZ(ALU.ADD) ;
    }
    else {
        putvalue(ALU_setNZ(ALU.ADD)) ;
    }
}

static void ror() {
    ALU.CI = STATUS.data.bit(STATUS_DATA_C)->v() ;
    ALU.ADD = (ALU.B >> 1) | (ALU.CI << 7) ;
    ALU.CO = ALU.B & 1 ;
    ALU_setC() ;

    if ((INST & 0xF) == 0xA){
        ALU.ACC = ALU_setNZ(ALU.ADD) ;
    }
    else {
        putvalue(ALU_setNZ(ALU.ADD)) ;
    }
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
    ADDR.EA = 0  | pull8() ;
    ADDR.EA = ADDR.EA | (pull8() << 8) ;
    ADDR.PC = ADDR.EA + 1;
}

static void sbc() {
    ALU.CI = STATUS.data.bit(STATUS_DATA_C)->v() ;
    ALU.A = ALU.ACC ;
    ALU.B = ALU.B ^ 0x00FF ; 
    ALU_add(1) ;
    ALU_setC() ;
    ALU.ACC = ALU_setNZ(ALU.ADD) ;
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
    putvalue(ALU.ACC);
}

static void stx() {
    putvalue(ALU.X);
}

static void sty() {
    putvalue(ALU.Y);
}

static void tax() {
    ALU.X = ALU_setNZ(ALU.ACC) ;
}

static void tay() {
    ALU.Y = ALU_setNZ(ALU.ACC);
}

static void tsx() {
    ALU.X = ALU_setNZ(ADDR.SP) ;
}

static void txa() {
    ALU.ACC = ALU_setNZ(ALU.X) ;
}

static void txs() {
    ADDR.SP = ALU.X ;
}

static void tya() {
    ALU.ACC = ALU_setNZ(ALU.Y) ;
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
    ADDR.PC = (uint16_t)read6502(0xFFFC) | ((uint16_t)read6502(0xFFFD) << 8);
    ALU.ACC = 0 ;
    ALU.X = 0 ;
    ALU.Y = 0 ;
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
    ADDR.PC = (uint16_t)read6502(0xFFFA) | ((uint16_t)read6502(0xFFFB) << 8);
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
    ADDR.PC = (uint16_t)read6502(0xFFFE) | ((uint16_t)read6502(0xFFFF) << 8);
}

uint8_t callexternal = 0;
void (*loopexternal)();


void step6502() {
    INST = read6502(ADDR.PC++);

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

    reset6502() ;
    ADDR.PC = 0x0400 ;

    exec6502() ;
}