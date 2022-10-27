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
output<1> Ah2D_e, Al2D_e ;

reg<8> EAh, EAl, PCh, PCl, SPh, SP ;
output<1> EAh_s, EAh_e, EAl_s, EAl_e, PCh_s, PCh_e, PCl_s, PCl_e, SPh_s, SPh_e, SP_s, SP_e ;

RAM RAM ;
output<1> RAM_s, RAM_e ;


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
output<1> ACC_s, ACC_e ;
reg<8> A, B, ADD ;
output<1> A_s, A_e, B_s, B_e, ADD_s, ADD_e ;
reg<8> X, Y ;
output<1> X_s, X_e, Y_s, Y_e ;

ALU ALU ;
output<4> ALU_op ;
tristate<8> ALU2D ;
output<1> ALU_e ;

STATUS STATUS ;
output<1> STATUS_i_in, STATUS_b_in ;
output<1> STATUS_nz_set, STATUS_v_set, STATUS_i_set, STATUS_c_set, STATUS_alu_c_set, STATUS_alu_c_from_C ;
output<1> STATUS_data_enable, STATUS_src_data ;
output<8> STATUS_data_in ;

reg<8> INST ;
output<1> INST_s, INST_e ;


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

    SPh_e.connect(SPh.enable) ;
    SPh_s.connect(SPh.set) ;
    SPh = 0x01 ;
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

    ADD_e.connect(ADD.enable) ;
    ADD_s.connect(ADD.set) ;
    ADD.data_out.connect(DATA.data_in) ;

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
    ALU.res.connect(ADD.data_in) ;
    ALU.res.connect(ALU2D.data_in) ;
    ALU_e.connect(ALU2D.enable) ;
    ALU2D.data_out.connect(DATA.data_in) ;
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
    STATUS_alu_c_set.connect(STATUS.alu_c_set) ;
    STATUS_alu_c_from_C.connect(STATUS.alu_c_from_C) ;
    STATUS_data_enable.connect(STATUS.data_enable) ;
    STATUS_src_data.connect(STATUS.src_data) ;
    STATUS_data_in.connect(STATUS.data_in) ;
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

void setaluc(){
    STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; 
}

void setalucfromC(){
    STATUS_alu_c_from_C = 1 ; STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; STATUS_alu_c_from_C = 0 ;  
}

void setNZ(){
    STATUS_nz_set = 1 ; STATUS_nz_set = 0 ;  
}

/*
void setI(uint8_t i){
    STATUS_i_in = i ; 
    STATUS_i_set = 1 ; STATUS_i_set = 0 ;
    STATUS_i_in = 0 ; 
}
*/

uint8_t pull8() {
    SP = SP + 1 ;
    return RAM._mem[SPh][SP] ;
}


//addressing mode functions, calculates effective addresses
static void imp() { //implied
}

static void acc() { //accumulator
}

static void imm() { //immediate, 1 cycle
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; // B = MEM_readhl(PCh, PCl) ;
}

static void zp() { //zero-page, 3 cycles
    EAh_s = 1 ; EAh_s = 0 ;
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; EAl_s = 1 ; EAl_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; // EAl = MEM_readhl(PCh, PCl) ;
    EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; incPC() ; // B = MEM_readhl(EAh, EAl) 
}

static void zpx() { //zero-page,X, 5 cycles
    EAh_s = 1 ; EAh_s = 0 ;
    X_e = 1 ; A_s = 1 ; A_s = 0 ; X_e = 0 ; // A = X ;
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; // B = MEM_readhl(PCh, PCl) ;
    ALU_op = ALU_ADD ; ALU_e = 1 ; EAl_s = 1 ; EAl_s = 0 ; ALU_e = 0 ; // EAl = ALU ;
    EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; incPC() ; // B = MEM_readhl(EAh, EAl) 
}

static void zpy() { //zero-page,Y, 5 cycles
    EAh_s = 1 ; EAh_s = 0 ;
    Y_e = 1 ; A_s = 1 ; A_s = 0 ; Y_e = 0 ; // A = Y ;
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; // B = MEM_readhl(PCh, PCl) ;
    ALU_op = ALU_ADD ; ALU_e = 1 ; EAl_s = 1 ; EAl_s = 0 ; ALU_e = 0 ; // EAl = ALU ;
    EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; incPC() ; // B = MEM_readhl(EAh, EAl) 
}

static void rel() { //relative for branch ops (8-bit immediate value, sign-extended), 7 cycles
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; A_s = 1 ; B_s = 1 ; A_s = 0 ; B_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; // A = MEM_readhl(PCh, PCl) ; B = MEM_readhl(PCh, PCl)
    ALU_op = ALU_SXT ; ALU_e = 1 ; EAh_s = 1 ; EAh_s = 0 ; ALU_e = 0 ; // EAh = ALU ;
    PCl_e = 1 ; Al2D_e = 1 ; B_s = 1 ; B_s = 0 ; Al2D_e = 0 ; PCl_e = 0 ; // B = PCl ;
    ALU_op = ALU_ADD ; ALU_e = 1 ; EAl_s = 1 ; STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; EAl_s = 0 ; ALU_e = 0 ; // EAl = ALU ;
    EAh_e = 1 ; Ah2D_e = 1 ; A_s = 1 ; A_s = 0 ; Ah2D_e = 0 ; EAh_e = 0 ; // A = EAh ;
    PCh_e = 1 ; Ah2D_e = 1 ; B_s = 1 ; B_s = 0 ; Ah2D_e = 0 ; PCh_e = 0 ; // B = PCh ;
    ALU_op = ALU_ADC ; ALU_e = 1 ; EAh_s = 1 ; EAh_s = 0 ; ALU_e = 0 ; // EAh = ALU ;
}

static void abso() { //absolute, 3 cycles
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; EAl_s = 1 ; EAl_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; // EAl = MEM_readhl(PCh, PCl) ; incPC() ;
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; EAh_s = 1 ; EAh_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; // EAh = MEM_readhl(PCh, PCl) ; incPC() ;
    EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; // B = MEM_readhl(EAh, EAl) 
}

static void absx() { //absolute,X, 7 cycles
    X_e = 1 ; A_s = 1 ; A_s = 0 ; X_e = 0 ; // A = X ;
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; // B = MEM_readhl(PCh, PCl) ;
    ALU_op = ALU_ADD ; ALU_e = 1 ; EAl_s = 1 ; STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; EAl_s = 0 ; ALU_e = 0 ; // EAl = ALU ; 
    A_s = 1 ; A_s = 0 ; // A = 0 ; 
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; // B = MEM_readhl(PCh, PCl) ;
    ALU_op = ALU_ADC ; ALU_e = 1 ; EAh_s = 1 ; EAh_s = 0 ; ALU_e = 0 ; // EAh = ALU ;
    EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; // B = MEM_readhl(EAh, EAl) 
}

static void absy() { //absolute,Y, 7 cycles
    Y_e = 1 ; A_s = 1 ; A_s = 0 ; Y_e = 0 ; // A = Y ;
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; // B = MEM_readhl(PCh, PCl) ;
    ALU_op = ALU_ADD ; ALU_e = 1 ; EAl_s = 1 ; STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; EAl_s = 0 ; ALU_e = 0 ; // EAl = ALU ; 
    A_s = 1 ; A_s = 0 ; // A = 0 ; 
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; // B = MEM_readhl(PCh, PCl) ;
    ALU_op = ALU_ADC ; ALU_e = 1 ; EAh_s = 1 ; EAh_s = 0 ; ALU_e = 0 ; // EAh = ALU ;
    EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; // B = MEM_readhl(EAh, EAl) 
}

static void ind() { //indirect, 8 cycles
    // Load ADDR_EAl and B at the same time
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; EAl_s = 1 ; B_s = 1 ; B_s = 0 ; EAl_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; // EAl = MEM_readhl(PCh, PCl) ; incPC() ;
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; EAh_s = 1 ; EAh_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; // EAh = MEM_readhl(PCh, PCl) ; incPC() ;
    EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; A_s = 1 ; A_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; // B = MEM_readhl(EAh, EAl) 
    ALU_op = ALU_INC ; ALU_e = 1 ; EAl_s = 1 ; EAl_s = 0 ; ALU_e = 0 ; // EAl = ALU ;
    EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; // B = MEM_readhl(EAh, EAl) 
    // We need to bring A to EAl and B to EAh
    ALU_op = ALU_PASS ; ALU_e = 1 ; EAh_s = 1 ; EAh_s = 0 ; ALU_e = 0 ; // EAh = ALU ;
    B_s = 1 ; B_s = 0 ; // B = 0 ; 
    ALU_op = ALU_ADD ; ALU_e = 1 ; EAl_s = 1 ; EAl_s = 0 ; ALU_e = 0 ; // EAl = ALU ;
}

static void indx() { // (indirect,X), 10 cycles
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; // B = MEM_readhl(PCh, PCl) ;
    X_e = 1 ; A_s = 1 ; A_s = 0 ; X_e = 0 ; // A = X ;
    ALU_op = ALU_ADD ; ALU_e = 1 ; EAl_s = 1 ; EAl_s = 0 ; ALU_e = 0 ;
    EAl_e = 1 ; Al2D_e = 1 ; B_s = 1 ; B_s = 0 ; Al2D_e = 0 ; EAl_e = 0 ;    
    ALU_op = ALU_INC ; ALU_e = 1 ; EAl_s = 1 ; EAl_s = 0 ; ALU_e = 0 ;
    EAl_e = 1 ; RAM_e = 1 ; EAh_s = 1 ; EAh_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; // EAh = MEM_read(0, EAl) ;
    ALU_op = ALU_PASS ; ALU_e = 1 ; EAl_s = 1 ; EAl_s = 0 ; ALU_e = 0 ; 
    EAl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; // B = MEM_readhl(0, EAl) ;
    ALU_op = ALU_PASS ; ALU_e = 1 ; EAl_s = 1 ; EAl_s = 0 ; ALU_e = 0 ; 
    EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; // B = MEM_readhl(EAh, EAl) 
}

static void indy() { // (indirect),Y, 11 cycles
    PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; // B = MEM_readhl(PCh, PCl) ;
    Y_e = 1 ; A_s = 1 ; A_s = 0 ; Y_e = 0 ; // A = Y ;
    ALU_op = ALU_INC ; ALU_e = 1 ; EAl_s = 1 ; EAl_s = 0 ; ALU_e = 0 ;
    EAl_e = 1 ; RAM_e = 1 ; EAh_s = 1 ; EAh_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; // EAh = MEM_read(0, EAl) ;
    ALU_op = ALU_PASS ; ALU_e = 1 ; EAl_s = 1 ; EAl_s = 0 ; ALU_e = 0 ; 
    EAl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; // B = MEM_readhl(0, EAl) ;
    ALU_op = ALU_ADD ; ALU_e = 1 ; EAl_s = 1 ; STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; EAl_s = 0 ; ALU_e = 0 ; // EAl = ADD ;
    A_s = 1 ; A_s = 0 ; // A = 0 ;
    EAh_e = 1 ; Ah2D_e = 1 ; B_s = 1 ; B_s = 0 ; Ah2D_e = 0 ; EAh_e = 0 ; 
    ALU_op = ALU_ADC ; ALU_e = 1 ; EAh_s = 1 ; EAh_s = 0 ; ALU_e = 0 ; // EAh = ADD ;
    EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; B_s = 1 ; B_s = 0 ; RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; // B = MEM_readhl(EAh, EAl) 
}


//instruction handler functions
static void adc() { // 2 cycles
    STATUS_alu_c_from_C = 1 ; ACC_e = 1 ; 
        A_s = 1 ; A_s = 0 ; STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; 
            STATUS_alu_c_from_C = 0 ; ACC_e = 0 ; // A = ACC 
    ALU_op = ALU_ADC ; ALU_e = 1 ; 
        ACC_s = 1 ; ACC_s = 0 ; setC() ; setV() ; setNZ() ; 
            ALU_e = 0 ; // ACC = ALU ; 
}

static void and_() { // 3 cycles
    ACC_e = 1 ; 
        A_s = 1 ; A_s = 0 ; 
            ACC_e = 0 ; // A = ACC ;
    ALU_op = ALU_AND ; ALU_e = 1 ; 
        ACC_s = 1 ; ACC_s = 0 ; setNZ() ; 
            ALU_e = 0 ; // ACC = ADD ; 
}

static void asl() { // 2 cycles
    ACC_e = 1 ; A_s = 1 ; B_s = 1 ; A_s = 0 ; B_s = 0 ; ACC_e = 0 ; // A = ACC ; B = ACC ;
    if ((INST & 0xF) == 0xA){
        ALU_op = ALU_ADD ; ALU_e = 1 ; 
            ACC_s = 1 ; ACC_s = 0 ; setC() ; setNZ() ; 
                ALU_e = 0 ; // ACC = ALU ;
    }
    else {
        ALU_op = ALU_ADD ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; 
            RAM_s = 1 ; RAM_s = 0 ; setC() ; setNZ() ;
                ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; // RAM[EA] = ALU
    }
}

static void bcc(){ // 2 cycle
    if (! STATUS.C){
        EAh_e = 1 ; Ah2D_e = 1 ; PCh_s = 1 ; PCh_s = 0 ; Ah2D_e = 0 ; EAh_e = 0 ;
        EAl_e = 1 ; Al2D_e = 1 ; PCl_s = 1 ; PCl_s = 0 ; Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void bcs() { // 2 cycle
    if (STATUS.C){
        EAh_e = 1 ; Ah2D_e = 1 ; PCh_s = 1 ; PCh_s = 0 ; Ah2D_e = 0 ; EAh_e = 0 ;
        EAl_e = 1 ; Al2D_e = 1 ; PCl_s = 1 ; PCl_s = 0 ; Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void beq(){ // 2 cycle
    if (STATUS.Z){
        EAh_e = 1 ; Ah2D_e = 1 ; PCh_s = 1 ; PCh_s = 0 ; Ah2D_e = 0 ; EAh_e = 0 ;
        EAl_e = 1 ; Al2D_e = 1 ; PCl_s = 1 ; PCl_s = 0 ; Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void bit() { // 2 cycles
    ACC_e = 1 ; 
        A_s = 1 ; A_s = 0 ; 
            ACC_e = 0 ; // A = ACC ;
    ALU_op = ALU_BIT ; 
        setV() ; setNZ() ;
}

static void bmi() { // 2 cycle
    if (STATUS.N){
        EAh_e = 1 ; Ah2D_e = 1 ; PCh_s = 1 ; PCh_s = 0 ; Ah2D_e = 0 ; EAh_e = 0 ;
        EAl_e = 1 ; Al2D_e = 1 ; PCl_s = 1 ; PCl_s = 0 ; Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void bne(){ // 2 cycle
    if (! STATUS.Z) {
        EAh_e = 1 ; Ah2D_e = 1 ; PCh_s = 1 ; PCh_s = 0 ; Ah2D_e = 0 ; EAh_e = 0 ;
        EAl_e = 1 ; Al2D_e = 1 ; PCl_s = 1 ; PCl_s = 0 ; Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void bpl() { // 2 cycle
    if (! STATUS.N) {
        EAh_e = 1 ; Ah2D_e = 1 ; PCh_s = 1 ; PCh_s = 0 ; Ah2D_e = 0 ; EAh_e = 0 ;
        EAl_e = 1 ; Al2D_e = 1 ; PCl_s = 1 ; PCl_s = 0 ; Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void brk() {
    /*
    incPC();
    push8(PCh) ;
    push8(PCl) ;
    STATUS_b_in = 1 ;  STATUS_data_enable = 1 ;
    push8(STATUS.data_out) ; //push CPU status to stack
    STATUS_data_enable = 0 ; STATUS_b_in = 0 ;
    setI(1) ;
    PCl = MEM_read(0xFFFE) ;
    PCh = MEM_read(0xFFFF) ;
    */
}

static void bvc() { // 2 cycle
    if (! STATUS.V) {
        EAh_e = 1 ; Ah2D_e = 1 ; PCh_s = 1 ; PCh_s = 0 ; Ah2D_e = 0 ; EAh_e = 0 ;
        EAl_e = 1 ; Al2D_e = 1 ; PCl_s = 1 ; PCl_s = 0 ; Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void bvs() { // 2 cycle
    if (STATUS.V) {
        EAh_e = 1 ; Ah2D_e = 1 ; PCh_s = 1 ; PCh_s = 0 ; Ah2D_e = 0 ; EAh_e = 0 ;
        EAl_e = 1 ; Al2D_e = 1 ; PCl_s = 1 ; PCl_s = 0 ; Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void clc() { // 2 cycle
    B_s = 1 ; B_s = 0 ; // B = 0 ;
    ALU_op = ALU_PASS ; 
        setC() ;
}

static void cld() {
}

static void cli() { // 1 cycle
    //setI(0) ;
}

static void clv() { // 2 cycle
    B_s = 1 ; B_s = 0 ; // B = 0 ;
    ALU_op = ALU_PASS ; 
        setV() ;
}

static void cmp() { // 2 cycles
    ACC_e = 1 ; 
        A_s = 1 ; A_s = 0 ; 
            ACC_e = 0 ; // A = ACC ;
    ALU_op = ALU_CMP ; 
        setC() ; setNZ() ; // don't save results
}

static void cpx() { // 2 cycles
    X_e = 1 ; 
        A_s = 1 ; A_s = 0 ; 
            X_e = 0 ; // A = X ;
    ALU_op = ALU_CMP ; 
        setC() ; setNZ() ; // don't save results
}

static void cpy() { // 2 cycles
    Y_e = 1 ; 
        A_s = 1 ; A_s = 0 ; 
            Y_e = 0 ; // A = Y ;
    ALU_op = ALU_CMP ; 
        setC() ; setNZ() ; // don't save results
}

static void dec() { // 1 cycles
    ALU_op = ALU_DEC ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; 
        RAM_s = 1 ; RAM_s = 0 ; setNZ() ; 
            ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; // RAM[EA] = ALU
}

static void dex() { // 2 cycles
    X_e = 1 ; 
        B_s = 1 ; B_s = 0 ; 
            X_e = 0 ; // B = X ;
    ALU_op = ALU_DEC ; ALU_e = 1 ; 
        X_s = 1 ; X_s = 0 ; setNZ() ; 
            ALU_e = 0 ; // X = ALU ; 
}

static void dey() { // 2 cycles
    Y_e = 1 ; 
        B_s = 1 ; B_s = 0 ; 
            Y_e = 0 ; // B = Y ;
    ALU_op = ALU_DEC ; ALU_e = 1 ; 
        Y_s = 1 ; Y_s = 0 ; setNZ() ; 
            ALU_e = 0 ; // Y = ALU ;
}

static void eor() {
    ACC_e = 1 ; 
        A_s = 1 ; A_s = 0 ; 
            ACC_e = 0 ; // A = ACC ;
    ALU_op = ALU_EOR ; ALU_e = 1 ; 
        ACC_s = 1 ; ACC_s = 0 ; setNZ() ; 
            ALU_e = 0 ; // ACC = ALU ; 
}

static void inc() {
    ALU_op = ALU_INC ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; 
        RAM_s = 1 ; RAM_s = 0 ; setNZ() ; 
            ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
}

static void inx() {
    X_e = 1 ; B_s = 1 ; B_s = 0 ; X_e = 0 ; // B = X ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
        X_s = 1 ; X_s = 0 ; setNZ() ; 
            ALU_e = 0 ; // X = ALU ;
}

static void iny() {
    Y_e = 1 ; B_s = 1 ; B_s = 0 ; Y_e = 0 ; // B = Y ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
        Y_s = 1 ; Y_s = 0 ; setNZ() ; 
            ALU_e = 0 ; // Y = ALU ;
}

static void jmp() {
    EAh_e = 1 ; Ah2D_e = 1 ; 
        PCh_s = 1 ; PCh_s = 0 ; 
            Ah2D_e = 0 ; EAh_e = 0 ;
    EAl_e = 1 ; Al2D_e = 1 ; 
        PCl_s = 1 ; PCl_s = 0 ; 
            Al2D_e = 0 ; EAl_e = 0 ;
}

static void jsr() { // 9 cycles
    PCh_e = 1 ; Ah2D_e = 1 ; 
        A_s = 1 ; A_s = 0 ; 
            Ah2D_e = 0 ; PCh_e = 0 ; // A = PCh ;
    PCl_e = 1 ; Al2D_e = 1 ; 
        B_s = 1 ; B_s = 0 ; 
            Al2D_e = 0 ; PCl_e = 0 ; // B = PCl ;
    ALU_op = ALU_DEC ; ALU_e = 1 ; 
        PCl_s = 1 ; STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; PCl_s = 0 ; 
            ALU_e = 0 ; // PCl = ALU ; 
    B_s = 1 ; B_s = 0 ; // B = 0 ;
    ALU_op = ALU_SBC ; SPh_e = 1 ; SP_e = 1 ; ALU_e = 1 ; 
        RAM_s = 1 ; RAM_s = 0 ; 
            ALU_e = 0 ; SP_e = 0 ; SPh_e = 0 ; 
                decSP() ; // push(ALU)
    PCl_e = 1 ; Al2D_e = 1 ; 
        B_s = 1 ; B_s = 0 ; 
            Al2D_e = 0 ; PCl_e = 0 ; // B = PCl ;
    ALU_op = ALU_PASS ; SPh_e = 1 ; SP_e = 1 ; ALU_e = 1 ; 
        RAM_s = 1 ; RAM_s = 0 ; 
            ALU_e = 0 ; SP_e = 0 ; SPh_e = 0 ; 
                decSP() ; // push(ALU)
    EAh_e = 1 ; Ah2D_e = 1 ; 
        PCh_s = 1 ; PCh_s = 0 ; 
            Ah2D_e = 0 ; EAh_e = 0 ;
    EAl_e = 1 ; Al2D_e = 1 ; 
        PCl_s = 1 ; PCl_s = 0 ; 
            Al2D_e = 0 ; EAl_e = 0 ;
}

static void lda() {
    ALU_op = ALU_PASS ; ALU_e = 1 ; 
        ACC_s = 1 ; ACC_s = 0 ; setNZ() ; 
            ALU_e = 0 ; // ACC = ALU ; 
}

static void ldx() {
    ALU_op = ALU_PASS ; ALU_e = 1 ; 
        X_s = 1 ; X_s = 0 ; setNZ() ; 
            ALU_e = 0 ; // X = ALU ; 
}

static void ldy() {
    ALU_op = ALU_PASS ; ALU_e = 1 ; 
        Y_s = 1 ; Y_s = 0 ; setNZ() ; 
            ALU_e = 0 ; // Y = ALU ;
}

static void lsr() {
    if ((INST & 0xF) == 0xA) {
        ALU_op = ALU_LSR ; ALU_e = 1 ; 
            ACC_s = 1 ; ACC_s = 0 ; setC() ; setNZ() ; 
                ALU_e = 0 ; // ACC = ALU ;
    }
    else {
        ALU_op = ALU_LSR ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; 
            RAM_s = 1 ; RAM_s = 0 ; setC() ; setNZ() ; 
                ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
    }
}

static void nop() {
}

static void ora() {
    ACC_e = 1 ; A_s = 1 ; A_s = 0 ; ACC_e = 0 ; // A = ACC ;
    ALU_op = ALU_ORA ; ADD_s = 1 ; ADD_s = 0 ; setNZ() ;
    ADD_e = 1 ; ACC_s = 1 ; ACC_s = 0 ; ADD_e = 0 ; // ACC = ADD ;
}

static void pha() {
    SPh_e = 1 ; SP_e = 1 ; ACC_e = 1 ; RAM_s = 1 ; RAM_s = 0 ; ACC_e = 0 ; SP_e = 0 ; SPh_e = 0 ; decSP() ;
}

static void php() {
    STATUS_b_in = 1 ; STATUS_data_enable = 1 ;
    SPh_e = 1 ; SP_e = 1 ; RAM_s = 1 ; RAM_s = 0 ; SP_e = 0 ; SPh_e = 0 ; decSP() ;
    STATUS_data_enable = 0 ; STATUS_b_in = 0 ;
}

static void pla() {
    B = pull8() ;
    ALU_op = ALU_PASS ; ADD_s = 1 ; ADD_s = 0 ; setNZ() ;
    ADD_e = 1 ; ACC_s = 1 ; ACC_s = 0 ; ADD_e = 0 ; // ACC = ADD ;
}

static void plp() {
    STATUS_data_in = pull8() ;
    STATUS_src_data = 1 ;
    STATUS_nz_set = 1 ; STATUS_v_set = 1 ; STATUS_i_set = 1 ; STATUS_c_set = 1 ;
    STATUS_nz_set = 0 ; STATUS_v_set = 0 ; STATUS_i_set = 0 ; STATUS_c_set = 0 ;
    STATUS_src_data = 0 ;
}

static void rol() {
    setalucfromC() ; 
    ALU_op = ALU_ROL ; ADD_s = 1 ; ADD_s = 0 ; setC() ; setNZ() ; 
    if ((INST & 0xF) == 0xA){
        ADD_e = 1 ; ACC_s = 1 ; ACC_s = 0 ; ADD_e = 0 ; // ACC = ADD ;
    }
    else {
        EAh_e = 1 ; EAl_e = 1 ; ADD_e = 1 ; RAM_s = 1 ; RAM_s = 0 ; ADD_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
    }
}

static void ror() {
    setalucfromC() ; 
    ALU_op = ALU_ROR ; ADD_s = 1 ; ADD_s = 0 ; setC() ; setNZ() ;
    if ((INST & 0xF) == 0xA){
        ADD_e = 1 ; ACC_s = 1 ; ACC_s = 0 ; ADD_e = 0 ; // ACC = ADD ;
    }
    else {
        EAh_e = 1 ; EAl_e = 1 ; ADD_e = 1 ; RAM_s = 1 ; RAM_s = 0 ; ADD_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
    }
}

static void rti() {
    STATUS_data_in = pull8() ;
    STATUS_src_data = 1 ;
    STATUS_nz_set = 1 ; STATUS_v_set = 1 ; STATUS_i_set = 1 ; STATUS_c_set = 1 ;
    STATUS_nz_set = 0 ; STATUS_v_set = 0 ; STATUS_i_set = 0 ; STATUS_c_set = 0 ;
    STATUS_src_data = 0 ;
    PCl = pull8() ;                 
    PCh = pull8() ; 
}

static void rts() {
    PCl = pull8() ;                 
    PCh = pull8() ; 
    incPC() ;
}

static void sbc() {
    setalucfromC() ; ACC_e = 1 ; A_s = 1 ; A_s = 0 ; ACC_e = 0 ; // A = ACC ; 
    ALU_op = ALU_SBC ; ADD_s = 1 ; ADD_s = 0 ; setC() ; setV() ; setNZ() ;
    ADD_e = 1 ; ACC_s = 1 ; ACC_s = 0 ; ADD_e = 0 ; // ACC = ADD ;
}

static void sec() {
    B_s = 1 ; B_s = 0 ; // B = 0 ;
    ALU_op = ALU_INC ; ADD_s = 1 ; ADD_s = 0 ;
    ADD_e = 1 ; B_s = 1 ; B_s = 0 ; ADD_e = 0 ; // B = ADD ;
    ALU_op = ALU_DEC ; setC() ;
}

static void sed() {
}

static void sei() {
    //setI(1) ;
}

static void sta() {
    EAh_e = 1 ; EAl_e = 1 ; ACC_e = 1 ; RAM_s = 1 ; RAM_s = 0 ; ACC_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
}

static void stx() {
    EAh_e = 1 ; EAl_e = 1 ; X_e = 1 ; RAM_s = 1 ; RAM_s = 0 ; X_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
}

static void sty() {
    EAh_e = 1 ; EAl_e = 1 ; Y_e = 1 ; RAM_s = 1 ; RAM_s = 0 ; Y_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
}

static void tax() {
    ACC_e = 1 ; B_s = 1 ; B_s = 0 ; ACC_e = 0 ; // B = ACC ;
    ALU_op = ALU_PASS ;
    ADD_s = 1 ; ADD_s = 0 ; setNZ() ;
    ADD_e = 1 ; X_s = 1 ; X_s = 0 ; ADD_e = 0 ; // X = ADD ; 
}

static void tay() {
    ACC_e = 1 ; B_s = 1 ; B_s = 0 ; ACC_e = 0 ; // B = ACC ;
    ALU_op = ALU_PASS ;
    ADD_s = 1 ; ADD_s = 0 ; setNZ() ;
    ADD_e = 1 ; Y_s = 1 ; Y_s = 0 ; ADD_e = 0 ; // Y = ADD ; 
}

static void tsx() {
    B = SP ;
    ALU_op = ALU_PASS ;
    ADD_s = 1 ; ADD_s = 0 ; setNZ() ;
    ADD_e = 1 ; X_s = 1 ; X_s = 0 ; ADD_e = 0 ; // X = ADD ; 
}

static void txa() {
    X_e = 1 ; B_s = 1 ; B_s = 0 ; X_e = 0 ; // B = X ;
    ALU_op = ALU_PASS ;
    ADD_s = 1 ; ADD_s = 0 ; setNZ() ;
    ADD_e = 1 ; ACC_s = 1 ; ACC_s = 0 ; ADD_e = 0 ; // ACC = ADD ; 
}

static void txs() {
    X_e = 1 ; B_s = 1 ; B_s = 0 ; X_e = 0 ; // B = X ;
    ALU_op = ALU_PASS ;
    ADD_s = 1 ; ADD_s = 0 ;
    ADD_e = 1 ; SP_s = 1 ; SP_s = 0 ; ADD_e = 0 ; // SP = ADD ; 
}

static void tya() {
    Y_e = 1 ; B_s = 1 ; B_s = 0 ; Y_e = 0 ; // B = Y ;
    ALU_op = ALU_PASS ;
    ADD_s = 1 ; ADD_s = 0 ; setNZ() ;
    ADD_e = 1 ; ACC_s = 1 ; ACC_s = 0 ; ADD_e = 0 ; // ACC = ADD ; 
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
    PCl = MEM_read(0xFFFC) ;
    PCh = MEM_read(0xFFFD) ;
    SP = 0xFD ;
}

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

uint8_t callexternal = 0;
void (*loopexternal)();
uint16_t SUCCESS_ADDR = 0 ;

void step6502() { 
    if ((PCh << 8 | PCl) == SUCCESS_ADDR){
        printf("SUCCESS!\n") ;
        exit(0) ;
    }
    INST = MEM_readhl(PCh, PCl) ; incPC() ; // 1 cycle

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
    uint8_t mem[0x10000] ;
    int nb = fread(mem, 0x10000, 1, file) ;
    for (int i = 0 ; i < 0x10000 ; i++){
        RAM._mem[i >> 8][i & 0xFF] = mem[i] ;
    }
    fclose(file) ;

    init6502() ;
    reset6502() ;
    PCh = 0x04 ;
    PCl = 0x00 ;

    exec6502() ;
}