#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#include "circuit.h"
#include "reg.h"
#include "bus.h"
#include "tristate.h"
#include "counter.h"
#include "not.h"

#include "RAM.h"
#include "ALU.h"
#include "STATUS.h"
#include "CTRL_IN.h"
#include "CTRL_OUT.h"
#include "CONTROL_ROMS.h"
#include "vectors.h"
#include "io.h"
#include "prog.h"
#include "programs.h"
#include "inst.h"

CONTROL_1_ROM C1 ;
CONTROL_2_ROM C2 ;
CONTROL_3_ROM C3 ;
CONTROL_4_ROM C4 ;
CONTROL_5_ROM C5 ;
CONTROL_UNIT CU(&C1, &C2, &C3, &C4, &C5) ;

output<1> ctrl_in_src ;
CTRL_IN CTRL_IN(&ctrl_in_src) ;
output<3> ctrl_out_cmd ;
CTRL_OUT CTRL_OUT(&ctrl_out_cmd) ;

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

counter<6> STEP ;
 
output<1> ctrl_PC_e(1) ;
not_<1> not_INST_s, not_PC_clr ;
output<8> ctrl_DATA ;

output<1> GND(0), VCC(1) ;

VECTORS VECTORS ;
IO IO ;

// Some globals useful for debugging.
int INST_CNT = 0 ;
int STEP_CNT = 0 ;
bool DEBUG_STEP = false ;


void init6502(){
    ctrl_DATA.drive(false) ;
    ctrl_DATA.connect(DATA.data_in) ;

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
    CTRL_OUT.PC_clr.connect(not_PC_clr.a) ;
    not_PC_clr.b.connect(PCl.clear) ;
    PCl.data_out.connect(PClt.data_in) ;
    C2.PC_e.connect(PClt.enable) ;
    PClt.data_out.connect(ADDRl.data_in) ;

    DATA.data_out.connect(PCh.data_in) ;
    C4.PCh_s.connect(PCh.load) ;
    PCl.co.connect(PCh.up) ;
    PCl.bo.connect(PCh.down) ;
    not_PC_clr.b.connect(PCh.clear) ;
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
    C1.A_s.connect(A.set) ;
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
    C5.ST_bi.connect(STATUS.i_in) ;

    C5.ST_NZ_s.connect(STATUS.nz_set) ;
    C5.ST_V_s.connect(STATUS.v_set) ;
    C5.ST_C_s.connect(STATUS.c_set) ;
    C5.ST_I_s.connect(STATUS.i_set) ;
    C5.ST_ALU_C_s.connect(STATUS.alu_c_set) ;
    C5.ST_ALU_C_from_C.connect(STATUS.alu_c_from_C) ;
    C5.ST_clk.connect(STATUS.clk) ;
    C3.ST_e.connect(STATUS.data_enable) ;
    C3.ST_src.connect(STATUS.src_data) ;
    DATA.data_out.connect(STATUS.data_in) ;
    STATUS.data_out.connect(DATA.data_in) ;

    DATA.data_out.connect(INST.data_in) ;
    C2.INST_s.connect(INST.set) ;
    INST_e.connect(INST.enable) ;
    INST_e = 0 ; // always enabled

    CTRL_OUT.CLK_async.connect(STEP.clk) ;
    CTRL_OUT.STEP_clr.connect(STEP.clear) ;
    VCC.connect(STEP.load) ;
    VCC.connect(STEP.enable) ;

    // Connect control unit.
    INST.data_out.connect(C1.inst) ;
    GND.connect(C1.n) ;
    GND.connect(C1.v) ;
    GND.connect(C1.z) ;
    GND.connect(C1.c) ;
    STEP.data_out.connect(C1.step) ;

    INST.data_out.connect(C2.inst) ;
    CTRL_OUT.PC_up.connect(C2.n) ;
    ctrl_PC_e.connect(C2.v) ;
    CTRL_OUT.INST_s.connect(not_INST_s.a) ;
    not_INST_s.b.connect(C2.z) ;
    CTRL_OUT.RAM_s.connect(C2.c) ;
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

    ADDRl.data_out.connect(CTRL_IN.addrl) ;
    RAM.ctrl.connect(CTRL_IN.ctrl1) ;
    C1.INST_done.connect(CTRL_IN.ctrl2) ;
    C2.RAM_e.connect(CTRL_IN.ctrl3) ;
    C2.RAM_s.connect(CTRL_IN.ctrl4) ;
}


void trace(){
    uint16_t pc = PCh << 8 | PCl ;
    uint16_t ea = EAh << 8 | EAl ;
    if (STEP_CNT == 0){
        printf("%8d  ", INST_CNT) ;
    }
    else {
        printf("          ") ;
    }
    printf("%2d PC:0x%04X INST:0x%02X SP:0x%02X STATUS:0x%02X A:0x%02X B:0x%02X ACC:0x%02X X:0x%02X Y:0x%02X EA:0x%04X RAM[EA]:0x%02X\n", 
        STEP_CNT, pc, (uint8_t)INST, (uint8_t)SP, STATUS.P(),
        (uint8_t)A, (uint8_t)B, (uint8_t)ACC, (uint8_t)X, (uint8_t)Y, ea, RAM.peek(ea)) ;
    //printf("drivers: %d\n", DATA.data_in.nb_drivers()) ;
}


uint8_t ctrl_cache = 0 ;
void process_ctrl(){
    //printf("ctrl addr:%02X cache:%02X\n", CTRL_IN.get_addr(), cache) ;
    if (! CTRL_IN.out3){   // RAM_e
        uint8_t addr = CTRL_IN.get_addr() ;
        // read from vectors or IO
        ctrl_DATA.drive(true) ;
        if (addr < 0xA){
            if (! ctrl_cache){
                ctrl_cache = IO.get_byte(addr) ;
                //printf("io read %d addr:%02X, data:%02X\n", step, addr, (uint8_t)ctrl_DATA) ;
            }
            ctrl_DATA = ctrl_cache ;
        }
        else {
            ctrl_DATA = VECTORS.get_byte(addr) ;
            // printf("vector read addr:%02X, data:%02X\n", addr, (uint8_t)ctrl_DATA) ;
        }
    }
    else {
        ctrl_cache = 0 ;
        ctrl_DATA.drive(false) ;
    }

    if (! CTRL_IN.out4){    // RAM_s
        uint8_t addr = CTRL_IN.get_addr() ;
        // write to vectors or IO
        if (addr < 0xA){
            IO.set_byte(addr, (uint8_t)DATA.data_out) ;
        }
        else {
            VECTORS.set_byte(addr, (uint8_t)DATA.data_out) ;
            // printf("vector write addr:%02X data:%02X\n", addr, (uint8_t)DATA.data_out) ;
        }
    }
}


int process_inst(uint8_t max_steps = 0xFF){
    if (DEBUG_STEP){
        trace() ;
    }

    bool prev_ctrl = false ;
    while (STEP_CNT < max_steps){

        CTRL_OUT.pulse(CLK_ASYNC) ;
        CTRL_OUT.pulse(CLK_SYNC) ;
        STEP_CNT++ ;

        // Check if the controller needs to do something
        if (CTRL_IN.out1){ // RAM.ctrl
            process_ctrl() ;
            prev_ctrl = true ;
        }
        else if (prev_ctrl){
            ctrl_cache = 0 ;
            ctrl_DATA.drive(false) ;
            prev_ctrl = false ;
        }

        if (DEBUG_STEP){
            trace() ;
        }

        if (CTRL_IN.out2){ // INST_done
            int steps = STEP_CNT ; 
            CTRL_OUT.pulse(STEP_CLR) ;
            // In theory we should do process_ctrl here, but there is nthing happening on step 0...
            STEP_CNT = 0 ;
            INST_CNT++ ;
            return steps ;
        }
    }

    return STEP_CNT ;
}


void insert_inst(uint8_t opcode){
    CTRL_OUT.pulse(STEP_CLR) ;
    assert(CU.make_cw() == CU.get_default_cw()) ;
    ctrl_DATA.drive(true) ;
    ctrl_DATA = opcode ;
    ctrl_PC_e.toggle() ;
    CTRL_OUT.pulse(RAM_S) ;
    ctrl_PC_e.toggle() ;
    ctrl_DATA.drive(false) ;

    process_inst() ;
}


void reset6502(PROG *prog){
    // Clear step counter and program counter
    CTRL_OUT.pulse(STEP_CLR) ;
    CTRL_OUT.pulse(PC_CLR) ;

    // Initialize INST register to BOOT
    ctrl_DATA.drive(true) ;
    ctrl_DATA = INST_BOOT ;
    CTRL_OUT.pulse(INST_S) ;
    ctrl_DATA.drive(false) ;

    insert_inst(INST_RST1) ;

    CTRL_OUT.pulse(STEP_CLR) ;
    CTRL_OUT.pulse(PC_CLR) ;
    // Load the program to RAM
    uint8_t ram0 = 0 ;
    for (int data = prog->get_next_byte(), n = 0 ; data != -1 ; data = prog->get_next_byte(), n++){
        if (n == 0){
            ram0 = data ;
        }
        ctrl_DATA.drive(true) ;
        ctrl_DATA = data ;
        ctrl_PC_e.toggle() ;
        CTRL_OUT.pulse(RAM_S) ;
        ctrl_PC_e.toggle() ;
        ctrl_DATA.drive(false) ;
        CTRL_OUT.pulse(PC_UP) ;
    }
    printf("LOAD  -> %d program bytes loaded\n", prog->len()) ;
    assert(CU.make_cw() == CU.get_default_cw()) ;
    
    // Print program info
    prog->describe() ;
    printf("\n") ;

    // Now that program is transfered, install vectors in controller
    VECTORS.set_reset(prog->start_addr()) ;
    VECTORS.set_int(prog->int_addr()) ;
    VECTORS.set_nmi(prog->nmi_addr()) ;

    CTRL_OUT.pulse(PC_CLR) ;
    insert_inst(INST_RST2) ;
    // TODO: Inserting the RST2 instruction squished the byte at RAM[0], we must put it back (it was saved in ram0)
    /* This doenst work since PC is already at the reset vector value.
    ctrl_DATA.drive(true) ;
    ctrl_DATA = ram0 ;
    ctrl_PC_e.toggle() ;
    CTRL_OUT.pulse(RAM_S) ;
    ctrl_PC_e.toggle() ;
    ctrl_DATA.drive(false) ; */

    printf("RESET -> PC:0x%02X%02X  INST:0x%02X  SP:0x%02X  STREG:0x%02X  EA:0x%02X%02X\n", (uint8_t)PCh, (uint8_t)PCl, 
        (uint8_t)INST, (uint8_t)SP, (uint8_t)STATUS.sreg, (uint8_t)EAh, (uint8_t)EAl) ;
        printf("---\n") ;
}


void process_interrupt(uint8_t inst){    
    uint16_t pc = PCh.data_out << 8 | PCl.data_out ;
    printf("INTR  -> PC:0x%04X  INST:0x%02X  SREG:0x%02X  SP:0x%02X\n", pc, (uint8_t)INST, (uint8_t)STATUS.sreg, (uint8_t)SP) ;

    // Prime INST with our fake interrupt instruction. This will alter the normal
    // fetch stage. See fetch() in addrmodes.h
    ctrl_DATA.drive(true) ;
    ctrl_DATA = inst ;
    CTRL_OUT.pulse(INST_S) ;
    process_inst(2) ;    // The opcode it still on the data bus, the next 2 steps of fetch() will store it to EAl
    ctrl_DATA.drive(false) ;    // Reset the data bus
    process_inst() ;            // Finish the instruction
 
    pc = PCh.data_out << 8 | PCl.data_out ;
    printf("      <- PC:0x%04X  INST:0x%02X  SREG:0x%02X  SP:0x%02X  RAM[SP+1]:0x%02X  RAM[SP+2]:0x%02X  RAM[SP+3]:0x%02X\n", 
        pc, (uint8_t)INST, (uint8_t)STATUS.sreg, (uint8_t)SP, 
        RAM.peek(0x0100 | (((uint8_t)SP)+1)), RAM.peek(0x0100 | (((uint8_t)SP)+2)), RAM.peek(0x0100 | (((uint8_t)SP)+3))) ;

    // Reset INST register to resume normal operation. PC should now be set to the address of the proper ISR.
    ctrl_DATA.drive(true) ;
    ctrl_DATA = INST_NOP ;
    CTRL_OUT.pulse(INST_S) ;
    ctrl_DATA.drive(false) ;
}


bool caught_irq = false ;
bool caught_nmi = false ;
void int_handler(int signum){
    if (signum == SIGUSR1){ // INT
        // Process interrupt only if interrupt disable is off.
        if (! STATUS.I){
            caught_irq = true ;
        }
    }
    else if (signum == SIGUSR2){ // NMI    
        caught_nmi = true ;
    }
}


int main(int argc, char *argv[]){
    signal(SIGUSR1, int_handler) ;
    signal(SIGUSR2, int_handler) ;

    init6502() ;

    // Default program
    PROG *prog = &progTestSuite ;
    if ((argc >= 2)&&((access(argv[1], F_OK) == 0))){
        prog = new PROG(argv[1], argv[1]) ;
    }
    printf("\n") ;

    printf("INIT  -> PC:0x%02X%02X  INST:0x%02X  SP:0x%02X  STREG:0x%02X  EA:0x%02X%02X\n", (uint8_t)PCh, (uint8_t)PCl, 
        (uint8_t)INST, (uint8_t)SP, (uint8_t)STATUS.sreg, (uint8_t)EAh, (uint8_t)EAl) ;
    printf("PID is %d\n", getpid()) ;
    
    if (getenv("DEBUG_STEP")){
        DEBUG_STEP = true ;
    }

    // Reset the processor
    reset6502(prog) ;

    // Start processing instructions.
    int nb_steps = 0 ;
    uint16_t prev_pc = 0xFFFF ;
    int max_steps = 0 ; 
    uint8_t max_inst = 0 ;
    while (1) {
        uint16_t pc = PCh.data_out << 8 | PCl.data_out ;
        if (pc == prev_pc){
            bool done = prog->is_done(pc) ;

            printf("---\nTRAP! -> PC:0x%04X  SREG:0x%02X  NB_INST:%d  NB_STEPS:%d  MAX_STEPS:%d  MAX_STEPS_INST:0x%02X  %s! \n", 
                pc, (uint8_t)STATUS.sreg, INST_CNT, nb_steps, max_steps, max_inst,
                (done ? "SUCCESS" : "ERROR")) ;
            fflush(stdout) ;
            exit(! done) ;
        }
        prev_pc = pc ;

        int inst_steps = process_inst() ; 
        nb_steps += inst_steps ;
        if (inst_steps > max_steps){
            max_steps = inst_steps ;
            max_inst = INST ;
        }
        if ((INST_CNT % 100000) == 0){
            printf("%d instructions executed (pc:0x%04X).\n", INST_CNT, pc) ;
        }

        // Check for interrupts
        if (caught_irq){
            process_interrupt(INST_IRQ) ;
            caught_irq = false ;
        }
        if (caught_nmi){
            process_interrupt(INST_NMI) ;
            caught_nmi = false ;
        }
    }
}