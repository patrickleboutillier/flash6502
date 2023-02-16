#include "utils.h"

#define INST_MON     0x0F
#define INST_RST1    0x1F
#define INST_RST2    0x2F
#define INST_NOP     0xEA
#define INST_IRQ     0xFF
#define INST_NMI     0xFB


// Some globals useful for debugging.
bool DEBUG_MON = false ;
int MON_EVERY = 1000 ; 
bool DEBUG_STEP = false ;
unsigned long INST_CNT = 0 ;
int STEP_CNT = 0 ;

struct {
    uint16_t pc, ea ;
    uint8_t inst, sp, acc, x, y, status ;
} MONITOR ;

#define INST MONITOR.inst

#include "addrmodes.h"
#include "ops.h"

typedef uint8_t (*func6502)(uint8_t step) ;

PROGMEM const func6502 addrtable[256] = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |     */
/* 0 */     imp, indx,  imp,  imp,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, imp, /* 0 */
/* 1 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, imp, /* 1 */
/* 2 */    abso, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, imp, /* 2 */
/* 3 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, imp, /* 3 */
/* 4 */     imp, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, imp, /* 4 */
/* 5 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, imp, /* 5 */
/* 6 */     imp, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm,  ind, abso, abso, imp, /* 6 */
/* 7 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, imp, /* 7 */
/* 8 */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, imp, /* 8 */
/* 9 */     rel, indy,  imp, indy,  zpx,  zpx,  zpy,  zpy,  imp, absy,  imp, absy, absx, absx, absy, imp, /* 9 */
/* A */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, imp, /* A */
/* B */     rel, indy,  imp, indy,  zpx,  zpx,  zpy,  zpy,  imp, absy,  imp, absy, absx, absx, absy, imp, /* B */
/* C */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, imp, /* C */
/* D */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp,  imp, absx, absx, absx, imp, /* D */
/* E */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, imp, /* E */
/* F */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp,  imp, absx, absx, absx, imp  /* F */
} ;

PROGMEM const func6502 optable[256] = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |      */
/* 0 */      brk,  ora,  nop,  nop,  nop,  ora,  asl,  nop,  php,  ora,  asl,  nop,  nop,  ora,  asl,  mon, /* 0 */
/* 1 */      bpl,  ora,  nop,  nop,  nop,  ora,  asl,  nop,  clc,  ora,  nop,  nop,  nop,  ora,  asl,  rst1, /* 1 */
/* 2 */      jsr,  and_, nop,  nop,  bit_,  and_,  rol,  nop,  plp,  and_,  rol,  nop,  bit_,  and_,  rol,  rst2, /* 2 */
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


void trace(const char *label=nullptr){
  static char buf[128] ;

  if (label != nullptr){
    sprintf(buf, "%8s", label) ;
  }
  else {
    sprintf(buf, "%8ld", INST_CNT) ;
  }
  Serial.print(buf) ;

  if (STEP_CNT == 0){
    sprintf(buf, " %2d PC:0x%04X INST:0x%02X SP:0x%02X STATUS:0x%02X ACC:0x%02X X:0x%02X Y:0x%02X EA:0x%04X\n", 
      STEP_CNT, MONITOR.pc, MONITOR.inst, MONITOR.sp, MONITOR.status, MONITOR.acc, MONITOR.x, MONITOR.y, MONITOR.ea) ;
  }
  else {
    sprintf(buf, " %2d  INST:0x%02X", STEP_CNT, MONITOR.inst) ;
  }
  Serial.print(buf) ;
}


uint8_t ctrl_cache = 0 ;
void process_ctrl(){
  if (! analogRead2Digital(CTRL_ADDR3)){  // RAM_e.read()
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

  if (! analogRead2Digital(CTRL_ADDR2)){  // RAM_s.read()
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


const char *msg_fetch = "fetch" ;
const char *msg_addr = "addr" ;
const char *msg_oper = "oper" ; 
void process_inst(bool grab_inst=true, uint8_t max_step = 0xFF){
  // Update the flags values for use in branch instructions. 
  STATUS.latch() ;
  
  uint8_t step_offset = 0 ;
  bool fetch_done = false, addr_done = false ;
  bool prev_ctrl = false ; 
  while (STEP_CNT <= max_step){
    if (STEP_CNT > 0){
      // This already happened for step 0 when we called STEP_CLR
      CTRL_OUT.pulse(CLK_ASYNC) ;    
    }

    const char *msg = NULL ;
    if (! fetch_done){
      if (fetch(STEP_CNT)){
        msg = msg_fetch ;
        goto SYNC ;
      } 
      fetch_done = true ;
      step_offset = STEP_CNT ;
    }
    if (! addr_done){
      func6502 f = pgm_read_word(&(addrtable[INST])) ;
      if (f(STEP_CNT - step_offset)){
        msg = msg_addr ;
        goto SYNC ;
      }
      addr_done = true ;
      step_offset = STEP_CNT ;
    }

    {
      func6502 f = pgm_read_word(&(optable[INST])) ;
      if (f(STEP_CNT - step_offset)){
        msg = msg_oper ;
        goto SYNC ;
      }
    }
    
    SYNC:
    CTRL_OUT.pulse(CLK_SYNC) ;  

    if ((grab_inst)&&(STEP_CNT == 1)){
      MONITOR.inst = DATA.read() ;
    }

    if (MONITOR.inst == INST_MON){
      switch (STEP_CNT){
        case 1: MONITOR.pc = DATA.read() << 8 ; 
                break ;
        case 3: MONITOR.pc |= DATA.read() ; 
                break ;
      }
    }
    
    if (PINC & 0b100){ // A2, RAM.ctrl
      process_ctrl() ;
      prev_ctrl = true ;
    }
    else if (prev_ctrl){
      ctrl_cache = 0 ;
      DATA.reset() ;
    }
    
    if (DEBUG_MON){
      trace() ;
      if (DEBUG_STEP){
        Serial.print(F("  ")) ;
        Serial.print(msg) ;
        Serial.print(F(" ")) ;
        Serial.print(STEP_CNT - step_offset) ;
        Serial.print(" done...") ;
        while (! button_pressed(STEP)){} ;
      }
      Serial.println() ;
    }
                    
    if (INST_done){
      // Reset step counter.
      int steps = STEP_CNT ;
      CTRL_OUT.pulse(STEP_CLR) ;
      STEP_CNT = 0 ;
      if (MONITOR.inst != INST_MON){
        INST_CNT++ ;
      }
      return ;
    }

    STEP_CNT++ ;
  }
}


void insert_inst(uint8_t opcode){
  DATA.write(opcode) ;
  MONITOR.inst = opcode ;
  INST_s.pulse() ;
  DATA.reset() ;
}


void monitor(bool pc_only=false){
  uint8_t inst = MONITOR.inst ;
  insert_inst(INST_MON) ;
  process_inst(false) ;
  /*
  uint8_t step = 1 ;
  //Serial.println(" MON") ; while (! button_pressed(STEP)){} ;
  CTRL_OUT.pulse(CLK_ASYNC) ; mon(1) ;
  MONITOR.pc = DATA.read() << 8 ;
  //Serial.println(" MON PCH") ; while (! button_pressed(STEP)){} ;
  CTRL_OUT.pulse(CLK_ASYNC) ; mon(2) ;
  CTRL_OUT.pulse(CLK_ASYNC) ; mon(3) ;
  MONITOR.pc |= DATA.read() ;
  //Serial.println(" MON PCL") ; while (! button_pressed(STEP)){} ;
  CTRL_OUT.pulse(CLK_ASYNC) ; mon(4) ;
  */
  if (! pc_only){
    /*
    CTRL_OUT.pulse(CLK_ASYNC) ;// mon(step++) ;
    MONITOR.ea = DATA.read() << 8 ;
    Serial.println(" MON EAH") ; while (! button_pressed(STEP)){} ;
    CTRL_OUT.pulse(CLK_ASYNC) ; //mon(step++) ;
    CTRL_OUT.pulse(CLK_ASYNC) ; //mon(step++) ;
    MONITOR.ea |= DATA.read() ;
    Serial.println(" MON EAL") ; while (! button_pressed(STEP)){} ;
    CTRL_OUT.pulse(CLK_ASYNC) ; //mon(step++) ; 
    CTRL_OUT.pulse(CLK_ASYNC) ; //mon(step++) ;
    MONITOR.sp = DATA.read() ;
    Serial.println(" MON SP") ; while (! button_pressed(STEP)){} ;
    CTRL_OUT.pulse(CLK_ASYNC) ; //mon(step++) ;
    CTRL_OUT.pulse(CLK_ASYNC) ; //mon(step++) ;
    MONITOR.acc = DATA.read() ;
    Serial.println(" MON ACC") ; while (! button_pressed(STEP)){} ;
    CTRL_OUT.pulse(CLK_ASYNC) ; //mon(step++) ;
    CTRL_OUT.pulse(CLK_ASYNC) ; //mon(step++) ;
    MONITOR.x = DATA.read() ;
    Serial.println(" MON X") ; while (! button_pressed(STEP)){} ;
    CTRL_OUT.pulse(CLK_ASYNC) ; //mon(step++) ;
    CTRL_OUT.pulse(CLK_ASYNC) ; //mon(step++) ;
    MONITOR.y = DATA.read() ;
    Serial.println(" MON Y") ; while (! button_pressed(STEP)){} ;
    CTRL_OUT.pulse(CLK_ASYNC) ; //mon(step++) ;
    CTRL_OUT.pulse(CLK_ASYNC) ; //mon(step++) ;
    MONITOR.status = DATA.read() ;
    Serial.println(" MON ST") ; while (! button_pressed(STEP)){} ;
    CTRL_OUT.pulse(CLK_ASYNC) ; //mon(step++) ;
    */
  }
  //CTRL_OUT.pulse(STEP_CLR) ;
    
  // Replace original instruction
  insert_inst(inst) ;
}


void reset6502(PROG *prog){
  // Clear step counter and program counter
  CTRL_OUT.pulse(STEP_CLR) ;
  CTRL_OUT.pulse(PC_CLR) ;
  // Reset latches
  CTRL_OUT.pulse(CLK_SYNC) ;

  monitor() ;
  trace("INIT  ->") ;
  
  // Initialize INST register to RST1
  insert_inst(INST_RST1) ;
  process_inst(false) ;

  Serial.print(F("- Loading program to RAM...")) ;
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
  Serial.println(F("done")) ;
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
  process_inst(false) ;

  // We must place another instruction here because RST2 doesn't load the next instruction.
  insert_inst(INST_NOP) ;

  monitor() ;
  trace("RESET ->") ;
  Serial.println(F("---")) ;
}


void process_interrupt(uint8_t opcode){   
  uint8_t inst = MONITOR.inst ;
  monitor() ;
  trace("INTR  ->") ;
  
  insert_inst(opcode) ;
  
  DATA.write(opcode) ;        // Enable opcode onto the data bus
  process_inst(false, 2) ;    // The opcode it still on the data bus, the next 3 (0, 1, 2) steps of fetch() will store it to EAl
  DATA.reset() ;              // Reset the data bus
  process_inst(false) ;       // Finish the instruction

  monitor() ;
  trace("      <-") ;
  insert_inst(inst) ;
}


void loop(){
  // Start processing instructions.
  uint16_t prev_pc = 0xFFFF ;
  while (1) {
    if (HALTED){
      // Infinite loop...
      continue ;
    }
    monitor(true) ;
    if (MONITOR.pc == prev_pc){
      bool done = prog->is_done(MONITOR.pc) ;
      Serial.println(F("---")) ;
      monitor() ;
      trace("TRAP! ->") ;
      Serial.println(done ? F("\nSUCCESS :)") : F("\nERROR :(")) ;
      while (1){} ;
    } 
    prev_pc = MONITOR.pc ;

    /*if ((MONITOR.pc >= 0x35b2)&&(MONITOR.pc < 0x35b4)){
        DEBUG_MON = true ;
        DEBUG_STEP = true ;
    }
    else {
        DEBUG_MON = false ;       
        DEBUG_STEP = false ;
    } */
  
    if ((MON_EVERY)&&((INST_CNT % MON_EVERY) == 0)){
      trace() ; 
    }
    process_inst() ; 

    if (! DEBUG_STEP){
      if (button_pressed(STEP)){
        //DEBUG_STEP = true ;
        //DEBUG_MON = true ;
        process_interrupt(INST_NMI) ;
      }
    }
  }
}
