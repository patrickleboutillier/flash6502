#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "circuit.h"
#include "reg.h"
#include "bus.h"
#include "tristate.h"
#include "counter.h"

#include "RAM.h"
#include "ALU.h"
#include "STATUS.h"
#include "CONTROL_ROMS.h"
#include "vectors.h"
#include "io.h"
#include "prog.h"
#include "programs.h"


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

RAM RAM ;

reg<8> ACC ;
reg<8> A, B ;
output<1> A_e(1), B_e(1) ;
reg<8> X, Y ;

ALU ALU ;
bus<1> ALU_n, ALU_v, ALU_z, ALU_c ;
STATUS STATUS ;

reg<8> INST ;
output<1> INST_e(1) ;

// TODO: replace with 2 4-bit counters. Maybe?
counter<6> STEP ;
output<1> CLK(1) ; 

output<1> boot_RAM_s(1), boot_PC_e(1), boot_PC_up(1), boot_STEP_clr(1), boot_PC_clr, boot_STEP_cnt_e ;
output<8> boot_DATA ;

output<1> GND(0), VCC(1) ;

VECTORS VECTORS ;
IO IO ;


void init6502(){
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
    C2.RAM_e.connect(RAM.enable) ;
    C2.RAM_s.connect(RAM.set) ;
    RAM.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(EAh.data_in) ;
    C4.EAh_e.connect(EAh.enable) ;
    C4.EAh_s.connect(EAh.set) ;
    EAh.data_out.connect(ADDRh.data_in) ;

    DATA.data_out.connect(EAl.data_in) ;
    C4.EAl_e.connect(EAl.enable) ;
    C4.EAl_s.connect(EAl.set) ;
    EAl.data_out.connect(ADDRl.data_in) ;

    DATA.data_out.connect(PCl.data_in) ;
    C4.PCl_s.connect(PCl.load) ;
    C2.PC_up.connect(PCl.up) ;
    VCC.connect(PCl.down) ;
    boot_PC_clr.connect(PCl.clear) ;
    PCl.data_out.connect(PClt.data_in) ;
    C2.PC_e.connect(PClt.enable) ;
    PClt.data_out.connect(ADDRl.data_in) ;

    DATA.data_out.connect(PCh.data_in) ;
    C4.PCh_s.connect(PCh.load) ;
    PCl.co.connect(PCh.up) ;
    PCl.bo.connect(PCh.down) ;
    boot_PC_clr.connect(PCh.clear) ;
    PCh.data_out.connect(PCht.data_in) ;
    C2.PC_e.connect(PCht.enable) ;
    PCht.data_out.connect(ADDRh.data_in) ;

    DATA.data_out.connect(SP.data_in) ;
    C2.SP_s.connect(SP.load) ;
    VCC.connect(SP.up) ;
    C2.SP_down.connect(SP.down) ;
    GND.connect(SP.clear) ;
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
    ALU.res.connect(DATA.data_in) ;
    C3.ALU_e.connect(ALU.enable) ;
    ALU.n.connect(ALU_n.data_in) ;
    ALU.v.connect(ALU_v.data_in) ;
    ALU.z.connect(ALU_z.data_in) ;
    ALU.c.connect(ALU_c.data_in) ;
    ALU_n.data_out.connect(STATUS.n_in) ;
    ALU_v.data_out.connect(STATUS.v_in) ;
    ALU_z.data_out.connect(STATUS.z_in) ;
    ALU_c.data_out.connect(STATUS.c_in) ;

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
    C2.INST_s.connect(INST.set) ;
    INST_e.connect(INST.enable) ;
    INST_e = 0 ; // always enabled

    CLK.connect(STEP.clk) ;
    C1.STEP_clr.connect(STEP.clear) ;
    VCC.connect(STEP.load) ;
    boot_STEP_cnt_e.connect(STEP.enable) ;
    boot_STEP_cnt_e = 1 ;

    // Connect control unit.
    INST.data_out.connect(C1.inst) ;
    boot_STEP_clr.connect(C1.n) ;
    GND.connect(C1.v) ;
    GND.connect(C1.z) ;
    GND.connect(C1.c) ;
    STEP.data_out.connect(C1.step) ;

    INST.data_out.connect(C2.inst) ;
    boot_PC_up.connect(C2.n) ;
    boot_PC_e.connect(C2.v) ;
    boot_RAM_s.connect(C2.z) ;
    GND.connect(C2.c) ;
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


void process_ctrl(){
    uint8_t addr = ADDRl.data_out & 0xF ;
    if (! C2.RAM_e){
        // read from vectors or IO
        boot_DATA.drive(true) ;
        if (addr < 0xA){
            boot_DATA = IO.get_byte(addr) ;
        }
        else {
            boot_DATA = VECTORS.get_byte(addr) ;
        }
    }
    else {
        boot_DATA.drive(false) ;
    }

    if (! C2.RAM_s){
        // write to vectors or IO
        if (addr < 0xA){
            IO.set_byte(addr, (uint8_t)DATA.data_out) ;
        }
        else {
            VECTORS.set_byte(addr, (uint8_t)DATA.data_out) ;
        }
    }
}


int process_inst(){
    int nb_steps = 1 ;
    while (1){
        CLK.pulse() ;
        if (STEP == 0){
            break ;
        }
        nb_steps++ ;

        // Check if the controller needs to do something
        if (RAM.ctrl.get_value()){
            process_ctrl() ;
        }
    }

    // printf("INST:0x%02X, steps:%d\n", (uint8_t)INST, nb_steps) ;

    return nb_steps ;
}


void reset6502(PROG *prog){
    // Install vectors in controller
    VECTORS.set_reset(prog->start_addr()) ;
    VECTORS.set_int(prog->int_addr()) ;
    VECTORS.set_nmi(prog->nmi_addr()) ;

    boot_STEP_clr.pulse() ;
    // At this point, INST is driving the control signals with whatever random value it contains at startup.
    // The enabled control signals when step and phase are both 0 are PC_e and RAM_e (see fetch()).
    // By pulsing the CLK 3 times, we get to STEP 3, where all the control signals have their default values.
    CLK.pulse() ; CLK.pulse() ; CLK.pulse() ;
    assert(CU.make_cw() == CU.get_default_cw()) ;
    boot_PC_clr.pulse() ;

    boot_DATA.drive(true) ;
    boot_DATA = 0x02 ; // RST1 instruction
    boot_PC_e.toggle() ;
    boot_RAM_s.pulse() ;
    boot_PC_e.toggle() ;
    boot_DATA.drive(false) ;
    // Reset step/phase to 0 and run the instruction.
    boot_STEP_clr.pulse() ;
    process_inst() ;

    boot_STEP_clr.pulse() ;
    // Again, pulse the clock to the third phase to disable all control signals
    CLK.pulse() ; CLK.pulse() ; CLK.pulse() ;
    assert(CU.make_cw() == CU.get_default_cw()) ;
    boot_PC_clr.pulse() ;
    // Load the program to RAM
    for (int i = 0 ; i < prog->len() ; i++){
        boot_DATA.drive(true) ;
        boot_DATA = prog->get_byte(i) ;
        boot_PC_e.toggle() ; 
        boot_RAM_s.pulse() ;
        boot_PC_e.toggle() ;
        boot_DATA.drive(false) ;
        boot_PC_up.pulse() ;
    }
    printf("LOAD  -> %d program bytes loaded\n", prog->len()) ;
    assert(CU.make_cw() == CU.get_default_cw()) ;

    boot_DATA.drive(true) ;
    boot_DATA = 0x03 ; // RST2 instruction
    boot_PC_e.toggle() ;
    boot_RAM_s.pulse() ;
    boot_PC_e.toggle() ;
    boot_DATA.drive(false) ;
    // Reset step/phase to 0 and run the instruction.
    boot_STEP_clr.pulse() ;
    process_inst() ;

    boot_STEP_clr.pulse() ;
    printf("RESET -> PC:0x%02X%02X  SP:0x%X  STREG:0x%02X  EA:0x%02X%02X\n", (uint8_t)PCh, (uint8_t)PCl, 
        (uint8_t)SP, (uint8_t)STATUS.sreg, (uint8_t)EAh, (uint8_t)EAl) ;
        printf("---\n") ;
}


int main(int argc, char *argv[]){
    init6502() ;

    // Default program
    PROG *prog = &progTestSuite ;
    if (argc >= 2){
        if (strcmp(argv[1], "star") == 0){
            prog = &progStar ;
        }
    }
    prog->describe() ;
    printf("\n") ;

    // Reset the processor
    reset6502(prog) ;

    // Start processing instructions.
    int nb_insts = 0, nb_steps = 0 ;
    uint16_t prev_pc = 0xFFFF ;
    int max_steps = 0 ; 
    uint8_t max_inst = 0 ;
    while (1) {
        uint16_t pc = PCh.data_out << 8 | PCl.data_out ;
        // printf("PC:0x%04X, INST:0x%02X, STATUS:0x%02X\n", pc, (uint8_t)INST, (uint8_t)STATUS.sreg) ;
        if (pc == prev_pc){
            bool done = prog->is_done(pc) ;

            printf("---\nTRAP! -> PC:0x%04X  SREG:0x%02X  NB_INST:%d  NB_STEPS:%d  MAX_STEPS:%d  MAX_STEPS_INST:0x%02X  %s! \n", 
                pc, (uint8_t)STATUS.sreg, nb_insts, nb_steps, max_steps, max_inst,
                (done ? "SUCCESS" : "ERROR")) ;
            exit(! done) ;
        } 
        prev_pc = pc ;

        /*if (prog->is_done(pc)){
            printf("SUCCESS (%d instructions executed in %d steps)!\n", nb_insts, nb_steps) ;
            printf("  Largest instruction (0x%02X) has %d steps.\n", ) ;
            exit(0) ;
        }*/

        int inst_steps = process_inst() ; 
        nb_steps += inst_steps ;
        if (inst_steps > max_steps){
            max_steps = inst_steps ;
            max_inst = INST ;
        }
        nb_insts++ ;
        if ((nb_insts % 100000) == 0){
            printf("%d instructions executed.\n", nb_insts) ;
        }
    }
}