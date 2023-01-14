#include "inst.h"
#include "utils.h"
#include "addrmodes.h"
#include "ops.h"


typedef uint8_t (*func6502)(uint8_t step) ;

PROGMEM const func6502 addrtable[256] = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |     */
/* 0 */     imp, indx,  imp,  imp,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, abso, /* 0 */
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
/* D */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp,  imp, absx, absx, absx, absx, /* D */
/* E */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, abso, /* E */
/* F */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp,  imp, absx, absx, absx,  imp  /* F */
} ;

#define boot nop

PROGMEM const func6502 optable[256] = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |      */
/* 0 */      brk,  ora,  rst1, rst2,  nop,  ora,  asl,  nop,  php,  ora,  asl,  nop,  nop,  ora,  asl,  boot, /* 0 */
/* 1 */      bpl,  ora,  nop,  nop,  nop,  ora,  asl,  nop,  clc,  ora,  nop,  nop,  nop,  ora,  asl,  nop, /* 1 */
/* 2 */      jsr,  and_, nop,  nop,  bit_,  and_,  rol,  nop,  plp,  and_,  rol,  nop,  bit_,  and_,  rol,  nop, /* 2 */
/* 3 */      bmi,  and_, nop,  nop,  nop,  and_,  rol,  nop,  sec,  and_,  nop,  nop,  nop,  and_,  rol,  nop, /* 3 */
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
/* F */      beq,  sbc,  nop,  nop,  nop,  sbc,  inc,  nop,  sed,  sbc,  nop,  nmi,  nop,  sbc,  inc,  irq  /* F */
} ;


// Some globals useful for debugging.
bool DEBUG_MON = false ;
int MON_EVERY = 1000 ; 
bool DEBUG_STEP = false ;
unsigned long INST_CNT = 0 ;
int STEP_CNT = 0 ;


void trace(bool idle, bool ln = true){
  static char buf[128] ;
  sprintf(buf, "%8lu  INST:0x%02X", INST_CNT, INST) ;
  Serial.print(buf) ;
  if (idle){
      sprintf(buf, "  PC:0x%04X  EA:0x%04X  SP:0x%04X  ACC:%3u  X:%3u  Y:%3u",
        get_pc(), get_ea(), get_sp(), get_acc(), get_x(), get_y()) ;
      Serial.print(buf) ;
  }
  if (ln){
    Serial.println() ;
  }
}


void step6502(const char *msg, int step, bool idle = false){
  Serial.print(F("STEP  -> ")) ;
  trace(idle, false) ;
  Serial.print(F(" ")) ;
  Serial.print(msg) ;
  Serial.print(F(" ")) ;
  if (step < 0){
    Serial.print("X") ;    
  }
  else {
    Serial.print(step) ;
  }
  Serial.println() ;
  while (! button_pressed(STEP)){} ;
}


uint8_t ctrl_cache = 0 ;
void process_ctrl(){
    if (! RAM_e.read()){
        CTRL_src = 1 ;
        uint8_t addr = analogRead2Digital(CTRL_ADDR3) << 3 | analogRead2Digital(CTRL_ADDR2) << 2 | digitalRead(CTRL_ADDR1) << 1 | digitalRead(CTRL_ADDR0) ;  
        CTRL_src = 0 ;
        // read from vectors or IO
        if (addr < 0xA){
            if (! ctrl_cache){
                ctrl_cache = IO.get_byte(addr) ;
            }
            DATA.write(ctrl_cache) ;
        }
        else {
          DATA.write(VECTORS.get_byte(addr)) ;
        }
    }
    else {
        ctrl_cache = 0 ;
        DATA.reset() ;     
    }

    if (! RAM_s.read()){
        // write to vectors or IO
        CTRL_src = 1 ;
        uint8_t addr = analogRead2Digital(CTRL_ADDR3) << 3 | analogRead2Digital(CTRL_ADDR2) << 2 | digitalRead(CTRL_ADDR1) << 1 | digitalRead(CTRL_ADDR0) ;  
        CTRL_src = 0 ;
        if (addr < 0xA){
            IO.set_byte(addr, DATA.read()) ;
        }
        else {
            VECTORS.set_byte(addr, DATA.read()) ;
        }
    }
}


bool post_step(bool prev_ctrl, bool debug, const char *msg, uint8_t step){   
  CTRL_OUT.pulse(CLK_SYNC) ;  
    
  // bool ctrl = digitalRead(CTRL) ;
  bool ctrl = PINC & 0b100 ; // A2
  if (ctrl){
    process_ctrl() ; 
  }
  else if (prev_ctrl){
    DATA.reset() ;
  }
  
  if (debug){
    step6502(msg, step) ;
  }
  
  return ctrl ;
}


unsigned long process_inst(uint8_t start_step, uint8_t max_steps, bool debug){
    // Update the flags values for use in branch instructions. 
    STATUS.latch() ;
    
    uint8_t addr_start = 0, op_start = 0 ;
    bool fetch_done = false, addr_done = false ;
    bool prev_ctrl = 0, ctrl = 0 ; 
    for (uint8_t step = start_step ; step < max_steps ; step++){
        prev_ctrl = ctrl ;

        if (step > 0){
          CTRL_OUT.pulse(CLK_ASYNC) ;    
        }
   
        if (! fetch_done){
            if (fetch(step)){
                ctrl = post_step(prev_ctrl, debug, "fetch", step) ;
                continue ;
            } 
            fetch_done = true ;
            addr_start = step ;
        }
        if (! addr_done){
            func6502 f = pgm_read_word(&(addrtable[INST])) ;
            if (f(step - addr_start)){
                ctrl = post_step(prev_ctrl, debug, "addr", step - addr_start) ;
                continue ;
            }
            addr_done = true ;
            op_start = step ;
        }

        {
          func6502 f = pgm_read_word(&(optable[INST])) ;
          if (f(step - op_start)){
              ctrl = post_step(prev_ctrl, debug, "oper", step - op_start) ;
              continue ;
          }
        }
        
        // Reset step counter.
        CTRL_OUT.pulse(STEP_CLR) ;
        CTRL_OUT.pulse(CLK_SYNC) ;
        
        INST_CNT++ ;
        return INST_CNT ;
    }

    return INST_CNT ;
}


void insert_inst(uint8_t opcode){
    CTRL_OUT.pulse(STEP_CLR) ;
    DATA.write(opcode) ;
    PC_e.toggle() ;
    RAM_s.pulse() ;
    PC_e.toggle() ;
    DATA.reset() ;

    process_inst(0, 0xFF, false) ;
}


void reset6502(PROG *prog, uint16_t start_addr = 0xFF){
    // Clear step counter and program counter
    CTRL_OUT.pulse(STEP_CLR) ;
    CTRL_OUT.pulse(PC_CLR) ;
    // Reset latches
    CTRL_OUT.pulse(CLK_SYNC) ;

    // Initialize INST register to BOOT
    // Clear INST register
    DATA.write(INST_BOOT) ;
    INST_s.pulse() ;
    INST = INST_BOOT ;
    DATA.reset() ;

    insert_inst(INST_RST1) ;

    Serial.println(F("- Loading program to RAM...")) ;
    CTRL_OUT.pulse(STEP_CLR) ;
    CTRL_OUT.pulse(PC_CLR) ;
    // Load the program to RAM
    for (int data = prog->get_next_byte() ; data != -1 ; data = prog->get_next_byte()){
        DATA.write(data) ;
        PC_e.toggle() ; 
        RAM_s.pulse() ;
        PC_e.toggle() ;
        DATA.reset() ;
        PC_up.pulse() ;
    }        
    Serial.print(F("LOAD  -> ")) ;
    Serial.print(prog->len()) ;
    Serial.println(F(" program bytes loaded")) ;
    
    // Print program info
    prog->describe() ;
    Serial.println() ;

    // Now that program is transfered, install vectors in controller
    VECTORS.set_reset(prog->start_addr()) ;
    VECTORS.set_int(prog->int_addr()) ;
    VECTORS.set_nmi(prog->nmi_addr()) ;

    CTRL_OUT.pulse(STEP_CLR) ;
    insert_inst(INST_RST2) ;
    
    Serial.print(F("RESET -> ")) ;
    trace(true) ;
    Serial.println(F("---")) ;
}


void process_interrupt(uint8_t inst){   
    Serial.print(F("INTR  -> ")) ;
    trace(true) ;

    //DEBUG_MON = true ;
    //DEBUG_STEP = true ;
    
    // Prime INST with our fake interrupt instruction. This will alter the normal
    // fetch stage. See fetch() in addrmodes.h
    DATA.write(inst) ;
    INST_s.pulse() ;
    INST = inst ;
    process_inst(0, 3, DEBUG_STEP) ;        // The opcode it still on the data bus, the next 2 steps of fetch() will store it to EAl
    DATA.reset() ;                          // Reset the data bus
    process_inst(3, 0xFF, DEBUG_STEP) ;     // finish the instruction

    Serial.print(F("      <- ")) ;
    trace(true) ;
 
    //pc = PCh.data_out << 8 | PCl.data_out ;
    //printf("      <- PC:0x%04X  INST:0x%02X  SREG:0x%02X  SP:0x%02X  RAM[SP+1]:0x%02X  RAM[SP+2]:0x%02X  RAM[SP+3]:0x%02X\n", 
    //    pc, (uint8_t)INST, (uint8_t)STATUS.sreg, (uint8_t)SP, 
    //    RAM.peek(0x0100 | (((uint8_t)SP)+1)), RAM.peek(0x0100 | (((uint8_t)SP)+2)), RAM.peek(0x0100 | (((uint8_t)SP)+3))) ;
    
    // Reset INST register to resume normal operation. PC should now be set to the address of the proper ISR.
    DATA.write(INST_NOP) ;
    INST_s.pulse() ;
    INST = INST_NOP ;
    DATA.reset() ;
}


void loop(){
    // Start processing instructions.
    uint16_t prev_pc = 0xFFFF ;
    while (1) {
        uint16_t pc = get_pc() ;
        if (pc == prev_pc){
            bool done = prog->is_done(pc) ;
            Serial.print(F("---\nTRAP! -> ")) ;
            trace(true, false) ; 
            Serial.println(done ? F("\nSUCCESS :)") : F("\nERROR :(")) ;
            while (1){} ;
        } 
        prev_pc = pc ;

        /*if ((pc >= 0x35b2)&&(pc < 0x35b4)){
            DEBUG_MON = true ;
            DEBUG_STEP = true ;
        }
        else {
            DEBUG_MON = false ;       
            DEBUG_STEP = false ;
        } */
      
        if (DEBUG_MON){
            trace(true) ; 
        }
        if ((INST_CNT % MON_EVERY) == 0){
            trace(true) ; 
        }
        process_inst(0, 0xFF, DEBUG_STEP) ; 

        if (! DEBUG_STEP){
            if (button_pressed(STEP)){
                //DEBUG_STEP = true ;
                //DEBUG_MON = true ;
                process_interrupt(INST_NMI) ;
            }
        }
    }
}
