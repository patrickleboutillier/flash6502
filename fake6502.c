#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "circuit.h"
#include "or.h"
#include "and.h"
#include "reg.h"
#include "bus.h"
#include "tristate.h"
#include "counter.h"

#include "RAM.h"
#include "ALU.h"
#include "STATUS.h"
#include "CONTROL_ROMS.h"


CONTROL_1_ROM C1 ;
CONTROL_2_ROM C2 ;
CONTROL_3_ROM C3 ;
CONTROL_4_ROM C4 ;
CONTROL_5_ROM C5 ;
CONTROL_UNIT CU(&C1, &C2, &C3, &C4, &C5) ;

bus<8> DATA, ADDRh, ADDRl ;
tristate<8> Ah2D, Al2D ;

reg<8> EAh, EAl ;
counter_updown<8> SP, PCh, PCl ;
tristate<8> SPht, SPlt, PCht, PClt ;
output<8> SPh_v(0x01) ;
output<1> PC_down(1), SP_up(1), SP_clr, PC_clr ; // the signals are not used by the CU 

RAM RAM ;

reg<8> ACC ;
reg<8> A, B ;
output<1> A_e(1), B_e(1) ;
reg<8> X, Y ;

ALU ALU ;
tristate<8> ALU2D ;

STATUS STATUS ;

reg<8> INST ;
output<1> INST_e(1) ;

// TODO: replace with 2 4-bit counters. Maybe?
counter<6> STEP ;
output<1> STEP_clk(1), STEP_clr(1), STEP_s(1), STEP_cnt_e, CLK(1) ; 

or_<1> RAM_s ;
and_<1> PC_e, PC_up ;
output<1> boot_RAM_s, boot_PC_e(1), boot_PC_up(1) ;
output<8> boot_DATA ;

output<1> GND(0) ;


void init6502(bool gen_mc){
    boot_RAM_s.connect(RAM_s.a) ;
    boot_PC_e.connect(PC_e.a) ;
    boot_PC_up.connect(PC_up.a) ;
    boot_DATA.drive(false) ;
    boot_DATA.connect(DATA.data_in) ;

    ADDRh.data_out.connect(Ah2D.data_in) ;
    C4.Ah2D_e.connect(Ah2D.enable) ;
    Ah2D.data_out.connect(DATA.data_in) ;
    ADDRl.data_out.connect(Al2D.data_in) ;    
    C4.Al2D_e.connect(Al2D.enable) ;
    Al2D.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(RAM.data_in) ;
    ADDRh.data_out.connect(RAM.addrh) ;
    ADDRl.data_out.connect(RAM.addrl) ;
    C4.RAM_e.connect(RAM.enable) ;
    RAM_s.c.connect(RAM.set) ;
    C4.RAM_s.connect(RAM_s.b) ;
    RAM.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(EAh.data_in) ;
    C4.EAh_e.connect(EAh.enable) ;
    C4.EAh_s.connect(EAh.set) ;
    EAh.data_out.connect(ADDRh.data_in) ;

    DATA.data_out.connect(EAl.data_in) ;
    C2.EAl_e.connect(EAl.enable) ;
    C2.EAl_s.connect(EAl.set) ;
    EAl.data_out.connect(ADDRl.data_in) ;

    DATA.data_out.connect(PCl.data_in) ;
    C2.PCl_s.connect(PCl.load) ;
    C2.PC_up.connect(PC_up.b) ;
    PC_up.c.connect(PCl.up) ;
    PC_down.connect(PCl.down) ;
    PC_clr.connect(PCl.clear) ;
    PCl.data_out.connect(PClt.data_in) ;
    C2.PC_e.connect(PC_e.b) ;
    PC_e.c.connect(PClt.enable) ;
    PClt.data_out.connect(ADDRl.data_in) ;

    DATA.data_out.connect(PCh.data_in) ;
    C4.PCh_s.connect(PCh.load) ;
    PCl.co.connect(PCh.up) ;
    PCl.bo.connect(PCh.down) ;
    PC_clr.connect(PCh.clear) ;
    PCh.data_out.connect(PCht.data_in) ;
    PC_e.c.connect(PCht.enable) ;
    PCht.data_out.connect(ADDRh.data_in) ;

    DATA.data_out.connect(SP.data_in) ;
    C2.SP_s.connect(SP.load) ;
    SP_up.connect(SP.up) ;
    C2.SP_down.connect(SP.down) ;
    SP_clr.connect(SP.clear) ;
    SP.data_out.connect(SPlt.data_in) ;
    C2.SP_e.connect(SPlt.enable) ;
    SPlt.data_out.connect(ADDRl.data_in) ;

    SPh_v.connect(SPht.data_in) ;
    C2.SP_e.connect(SPht.enable) ;
    SPht.data_out.connect(ADDRh.data_in) ;

    DATA.data_out.connect(ACC.data_in) ;
    C1.ACC_e.connect(ACC.enable) ;
    C1.ACC_s.connect(ACC.set) ;
    ACC.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(A.data_in) ;
    A_e.connect(A.enable) ;
    C3.A_s.connect(A.set) ;
    A_e = 0 ; // always enabled 

    DATA.data_out.connect(B.data_in) ;
    B_e.connect(B.enable) ;
    C3.B_s.connect(B.set) ;
    B_e = 0 ; // always enabled  

    DATA.data_out.connect(X.data_in) ;
    C1.X_e.connect(X.enable) ;
    C1.X_s.connect(X.set) ;
    X.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(Y.data_in) ;
    C1.Y_e.connect(Y.enable) ;
    C1.Y_s.connect(Y.set) ;
    Y.data_out.connect(DATA.data_in) ;

    A.data_out.connect(ALU.a) ;
    B.data_out.connect(ALU.b) ;
    STATUS.alu_c.connect(ALU.c_in) ;
    C3.ALU_op.connect(ALU.op) ;
    ALU.res.connect(ALU2D.data_in) ;
    C3.ALU_e.connect(ALU2D.enable) ;
    ALU2D.data_out.connect(DATA.data_in) ;
    ALU.n.connect(STATUS.n_in) ;
    ALU.v.connect(STATUS.v_in) ;
    ALU.z.connect(STATUS.z_in) ;
    ALU.c.connect(STATUS.c_in) ;

    C5.ST_NZ_s.connect(STATUS.nz_set) ;
    C5.ST_V_s.connect(STATUS.v_set) ;
    C5.ST_C_s.connect(STATUS.c_set) ;
    C5.ST_ALU_C_s.connect(STATUS.alu_c_set) ;
    C5.ST_ALU_C_from_C.connect(STATUS.alu_c_from_C) ;
    C5.ST_s.connect(STATUS.set) ;
    C5.ST_e.connect(STATUS.data_enable) ;
    C5.ST_src.connect(STATUS.src_data) ;
    DATA.data_out.connect(STATUS.data_in) ;
    STATUS.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(INST.data_in) ;
    C4.INST_s.connect(INST.set) ;
    INST_e.connect(INST.enable) ;
    INST_e = 0 ; // always enabled

    CLK.connect(STEP.clk) ;
    STEP_clr.connect(STEP.clear) ;
    STEP_s.connect(STEP.load) ;
    STEP_cnt_e.connect(STEP.enable) ;
    STEP_cnt_e = 1 ;

    if (! gen_mc){
        INST.data_out.connect(C1.inst) ;
        GND.connect(C1.n) ;
        GND.connect(C1.v) ;
        GND.connect(C1.z) ;
        GND.connect(C1.c) ;
        STEP.data_out.connect(C1.step) ;

        INST.data_out.connect(C2.inst) ;
        STATUS.N.connect(C2.n) ;
        STATUS.V.connect(C2.v) ;
        STATUS.Z.connect(C2.z) ;
        STATUS.C.connect(C2.c) ;
        STEP.data_out.connect(C2.step) ;

        INST.data_out.connect(C3.inst) ;
        GND.connect(C3.n) ;
        GND.connect(C3.v) ;
        GND.connect(C3.z) ;
        GND.connect(C3.c) ;
        STEP.data_out.connect(C3.step) ;

        INST.data_out.connect(C4.inst) ;
        STATUS.N.connect(C4.n) ;
        STATUS.V.connect(C4.v) ;
        STATUS.Z.connect(C4.z) ;
        STATUS.C.connect(C4.c) ;
        STEP.data_out.connect(C4.step) ;

        INST.data_out.connect(C5.inst) ;
        GND.connect(C5.n) ;
        GND.connect(C5.v) ;
        GND.connect(C5.z) ;
        GND.connect(C5.c) ;
        STEP.data_out.connect(C5.step) ;
    }

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
/* 2 */      jsr,  anda,  nop,  rla,  bit,  anda,  rol,  rla,  plp,  anda,  rol,  nop,  bit,  anda,  rol,  rla, /* 2 */
/* 3 */      bmi,  anda,  nop,  rla,  nop,  anda,  rol,  rla,  sec,  anda,  nop,  rla,  nop,  anda,  rol,  rla, /* 3 */
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
    #define MICROCODE  1

    #if !MICROCODE
        uint8_t addr_start = 0, op_start = 0 ;
        bool fetch_done = false, addr_done = false, op_done = false ;
    #endif

    for (int i = 0 ; i < 16*4 ; i++){
        /*
        uint8_t step = STEP ;
        uint8_t phase = PHASE ;

        #if MICROCODE
            uint64_t cw = CU.get_cw(INST, STATUS.N << 3 | STATUS.V << 2 | STATUS.Z << 1 | STATUS.C, step, phase) ;
            CU.apply_cw(cw) ;
            // TODO: why does this test fail?
            //assert(CU.make_cw() == cw) ;
        #else
            uint8_t tick = step << 4 | phase ;
            if (! fetch_done){
                if (fetch(tick)){
                    uint64_t cw = CU.get_cw(INST, STATUS.N << 3 | STATUS.V << 2 | STATUS.Z << 1 | STATUS.C, step, phase) ;
                    assert(CU.make_cw() == cw) ;
                    continue ;
                } 
                fetch_done = true ;
                addr_start = step << 4 ;
            }
            if (! addr_done){
                if ((*addrtable[INST])(tick - addr_start)){
                    uint64_t cw = CU.get_cw(INST, STATUS.N << 3 | STATUS.V << 2 | STATUS.Z << 1 | STATUS.C, step, phase) ;
                    assert(CU.make_cw() == cw) ;
                    continue ;
                }
                addr_done = true ;
                op_start = step << 4 ;
            }
            if (! op_done){
                if ((*optable[INST])(tick - op_start)){
                    uint64_t cw = CU.get_cw(INST, STATUS.N << 3 | STATUS.V << 2 | STATUS.Z << 1 | STATUS.C, step, phase) ;
                    //if (CU.make_cw() != cw)
                    //    printf("INST:0x%02X FLAGS:0x%X STEP:0x%X PHASE:0x%X -> 0x%010lX != 0x%010lX\n", (uint8_t)INST, STATUS.N << 3 | STATUS.V << 2 | STATUS.Z << 1 | STATUS.C, step, phase,
                    //        CU.make_cw(), cw) ;
                    assert(CU.make_cw() == cw) ;
                    continue ;
                }
                // Optimization
                // return step ;
                else {
                    uint64_t cw = CU.get_cw(INST, STATUS.N << 3 | STATUS.V << 2 | STATUS.Z << 1 | STATUS.C, step, phase) ;
                    assert(CU.make_cw() == cw) ;
                }
            }
        #endif
        */

        CLK.pulse() ;
    }

    return 16*4 ;
}


void generate_microcode(){
    STEP_clr.pulse() ;
    // At this point, INST is driving the control signals with whatever random value it contains at startup.
    // The enabled control signals when step and phase are both 0 are PC_e and RAM_e (see fetch()).
    // By pulsing the CLK 3 times, we get to STEP 3, where all the control signals have their default values.
    CLK.pulse() ; CLK.pulse() ; CLK.pulse() ;
    assert(CU.make_cw() == CU.get_default_cw()) ;

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
                    printf("  /* INST:0x%02X FLAGS:0x%X STEP:0x%02X */ 0x%010lX,\n", inst, flags, step,
                        CU.make_cw()) ;
                    continue ;
                } 
                fetch_done = true ;
                addr_start = step ;
            }
            if (! addr_done){
                if ((*addrtable[inst])(step - addr_start)){
                    printf("  /* INST:0x%02X FLAGS:0x%X STEP:0x%02X */ 0x%010lX,\n", inst, flags, step,
                        CU.make_cw()) ;
                    continue ;
                }
                addr_done = true ;
                op_start = step ;
            }
            (*optable[inst])(step - op_start) ;
            printf("  /* INST:0x%02X FLAGS:0x%X STEP:0x%02X */ 0x%010lX,\n", inst, flags, step,
                CU.make_cw()) ;
        }
    }
    printf("} ;\n") ;
}


void reset6502(){
    STEP_clr.pulse() ;
    // At this point, INST is driving the control signals with whatever random value it contains at startup.
    // The enabled control signals when step and phase are both 0 are PC_e and RAM_e (see fetch()).
    // By pulsing the CLK 3 times, we get to STEP 3, where all the control signals have their default values.
    CLK.pulse() ; CLK.pulse() ; CLK.pulse() ;
    assert(CU.make_cw() == CU.get_default_cw()) ;
    PC_clr.pulse() ;

    boot_DATA.drive(true) ;
    boot_DATA = 0x02 ; // RST instruction
    boot_PC_e.toggle() ;
    boot_RAM_s.pulse() ;
    boot_PC_e.toggle() ;
    boot_DATA.drive(false) ;
    // Reset step/phase to 0 and run the instruction.
    STEP_clr.pulse() ;
    do_inst() ;
    STEP_clr.pulse() ;
    PC_clr.pulse() ;
    printf("RESET -> PC:0x%02X%02X, SP:0x%X, STATUS:0x%02X\n", (uint8_t)PCh, (uint8_t)PCl, (uint8_t)SP, (uint8_t)STATUS.sreg) ;
}


void load6502(uint8_t prog[], int prog_len){
    STEP_clr.pulse() ;
    // Again, pulse the clock to the third phase to disable all control signals
    CLK.pulse() ; CLK.pulse() ; CLK.pulse() ;
    assert(CU.make_cw() == CU.get_default_cw()) ;
    PC_clr.pulse() ;

    for (int i = 0 ; i < prog_len ; i++){
        boot_DATA.drive(true) ;
        boot_DATA = prog[i] ;
        boot_PC_e.toggle() ; 
        boot_RAM_s.pulse() ;
        boot_PC_e.toggle() ;
        boot_DATA.drive(false) ;
        boot_PC_up.pulse() ;
    }

    STEP_clr.pulse() ;
    PC_clr.pulse() ;
    printf("LOAD  -> %d bytes loaded starting at address 0x00 (PC is now 0x%02X%02X)\n", prog_len, (uint8_t)PCh, (uint8_t)PCl) ;
}


int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Usage: %s SUCCESS_ADDR_IN_HEX\n", argv[0]) ;
        exit(1) ;
    }

    uint16_t SUCCESS_ADDR = (uint16_t)strtol(argv[1], NULL, 16) ;
    init6502(SUCCESS_ADDR == 0) ;
 
    if (SUCCESS_ADDR == 0){
        generate_microcode() ;
        exit(0) ; 
    }
    printf("Default control word is 0x%010lX\n", CU.get_default_cw()) ;
    printf("Success address is 0x%X\n", SUCCESS_ADDR) ;
    

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
    uint16_t prev_pc = 0xFFFF ;
    while (1) {
        uint16_t pc = PCh.data_out << 8 | PCl.data_out ;
        //printf("PC:%04X, INST:0x%02X, STATUS:0x%02X\n", pc, (uint8_t)INST, (uint8_t)STATUS.sreg) ;
        if (pc == prev_pc){
            printf("Trap detected at 0x%04X! STATUS:0x%02X\n", pc, (uint8_t)STATUS.sreg) ;
            exit(1) ;
        } 
        prev_pc = pc ;

        if (pc == SUCCESS_ADDR){
            printf("SUCCESS (%d instructions executed in %d steps)!\n", nb_inst, nb_step) ;
            exit(0) ;
        }

        nb_step += do_inst() ;
        nb_inst++ ;
        if ((nb_inst % 100000) == 0){
            printf("%d instructions executed.\n", nb_inst) ;
        }
    }
}