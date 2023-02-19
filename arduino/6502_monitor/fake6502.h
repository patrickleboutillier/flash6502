#include "utils.h"

#define INST_PC      0x0F
#define INST_MON     0x1F
#define INST_RST1    0x2F
#define INST_RST2    0x3F
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
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |    */
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
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |       */
/* 0 */      brk,  ora,  nop,  nop,  nop,  ora,  asl,  nop,  php,  ora,  asl,  nop,  nop,  ora,  asl,  pc,   /* 0 */
/* 1 */      bpl,  ora,  nop,  nop,  nop,  ora,  asl,  nop,  clc,  ora,  nop,  nop,  nop,  ora,  asl,  mon,  /* 1 */
/* 2 */      jsr,  and_, nop,  nop,  bit_, and_, rol,  nop,  plp,  and_, rol,  nop,  bit_, and_, rol,  rst1, /* 2 */
/* 3 */      bmi,  and_, nop,  nop,  nop,  and_, rol,  nop,  sec,  and_, nop,  nop,  nop,  and_, rol,  rst2, /* 3 */
/* 4 */      rti,  eor,  nop,  nop,  nop,  eor,  lsr,  nop,  pha,  eor,  lsr,  nop,  jmp,  eor,  lsr,  nop,  /* 4 */
/* 5 */      bvc,  eor,  nop,  nop,  nop,  eor,  lsr,  nop,  cli_, eor,  nop,  nop,  nop,  eor,  lsr,  nop,  /* 5 */
/* 6 */      rts,  adc,  nop,  nop,  nop,  adc,  ror,  nop,  pla,  adc,  ror,  nop,  jmp,  adc,  ror,  nop,  /* 6 */
/* 7 */      bvs,  adc,  nop,  nop,  nop,  adc,  ror,  nop,  sei_, adc,  nop,  nop,  nop,  adc,  ror,  nop,  /* 7 */
/* 8 */      nop,  sta,  nop,  nop,  sty,  sta,  stx,  nop,  dey,  nop,  txa,  nop,  sty,  sta,  stx,  nop,  /* 8 */
/* 9 */      bcc,  sta,  nop,  nop,  sty,  sta,  stx,  nop,  tya,  sta,  txs,  nop,  nop,  sta,  nop,  nop,  /* 9 */
/* A */      ldy,  lda,  ldx,  nop,  ldy,  lda,  ldx,  nop,  tay,  lda,  tax,  nop,  ldy,  lda,  ldx,  nop,  /* A */
/* B */      bcs,  lda,  nop,  nop,  ldy,  lda,  ldx,  nop,  clv,  lda,  tsx,  nop,  ldy,  lda,  ldx,  nop,  /* B */
/* C */      cpy,  cmp,  nop,  nop,  cpy,  cmp,  dec,  nop,  iny,  cmp,  dex,  nop,  cpy,  cmp,  dec,  nop,  /* C */
/* D */      bne,  cmp,  nop,  nop,  nop,  cmp,  dec,  nop,  cld,  cmp,  nop,  nop,  nop,  cmp,  dec,  nop,  /* D */
/* E */      cpx,  sbc,  nop,  nop,  cpx,  sbc,  inc,  nop,  inx,  sbc,  nop,  sbc,  cpx,  sbc,  inc,  nop,  /* E */
/* F */      beq,  sbc,  nop,  nop,  nop,  sbc,  inc,  nop,  sed,  sbc,  nop,  nmi,  nop,  sbc,  inc,  irq   /* F */
} ;


void monitor_trace(const char *label=nullptr, bool nl=true){
  static char buf[128] ;

  if (label != nullptr){
    sprintf(buf, "%8s", label) ;
  }
  else {
    sprintf(buf, "%8ld", INST_CNT) ;
  }
  Serial.print(buf) ;

  if (STEP_CNT == 0){
    sprintf(buf, " %2d PC:0x%04X  INST:0x%02X  EA:0x%04X ACC:%-3d X:%-3d Y:%-3d SP:0x%02X STATUS:0x%02X", 
      STEP_CNT, MONITOR.pc, MONITOR.inst, MONITOR.ea, MONITOR.acc, MONITOR.x, MONITOR.y, MONITOR.sp, MONITOR.status) ;
    if (nl){
      strcat(buf, "\n") ;
    }
  }
  else {
    sprintf(buf, " %2d PC:0x%04X~ INST:0x%02X  ", STEP_CNT, MONITOR.pc, MONITOR.inst) ;
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


void process_monitor(bool grab_inst){
    // See fetch()
    if ((grab_inst)&&(STEP_CNT == 3)){
      MONITOR.inst = DATA.read() ;
    }

    // See pc()
    if (MONITOR.inst == INST_PC){
      switch (STEP_CNT){
        case 2: MONITOR.pc = DATA.read() << 8 ; 
                break ;
        case 4: MONITOR.pc |= DATA.read() ; 
                break ;
      }
    }
    // See mon()
    else if (MONITOR.inst == INST_MON){
      switch (STEP_CNT){
        case  2: MONITOR.pc = DATA.read() << 8 ; 
                 break ;
        case  4: MONITOR.pc |= DATA.read() ; 
                 break ;
        case  6: MONITOR.ea = DATA.read() << 8 ; 
                 break ;
        case  8: MONITOR.ea |= DATA.read() ; 
                 break ;
        case 10: MONITOR.sp = DATA.read() ; 
                 break ;
        case 12: MONITOR.acc = DATA.read() ; 
                 break ;
        case 14: MONITOR.x = DATA.read() ; 
                 break ;
        case 16: MONITOR.y = DATA.read() ; 
                 break ;
        case 18: MONITOR.status = DATA.read() ; 
                 break ;
        }
    }
}

const char *msg_fetch = "fetch" ;
const char *msg_addr = "addr" ;
const char *msg_oper = "oper" ; 
void process_inst(bool grab_inst=true, uint8_t max_step = 0xFF){
  // Update the flags values for use in branch instructions. 
  // No longer required with CRTL4 in place
  // STATUS.latch() ;
  
  uint8_t step_offset = 0 ;
  bool fetch_done = false, addr_done = false ;
  bool prev_ctrl = false ; 
  while (STEP_CNT <= max_step){    
    process_monitor(grab_inst) ;
    
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
    CLK_sync.pulse() ;  
        
    if (PINC & 0b100){ // A2, RAM.ctrl
      process_ctrl() ;
      prev_ctrl = true ;
    }
    else if (prev_ctrl){
      ctrl_cache = 0 ;
      DATA.reset() ;
    }
        
    if ((MONITOR.inst != INST_MON)&&(MONITOR.inst != INST_PC)){
      if ((DEBUG_MON)||(DEBUG_STEP)){
        monitor_trace(nullptr, false) ;
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
    }
               
    if (INST_done){
      // Reset step counter.
      int steps = STEP_CNT ;
      CTRL_OUT.pulse(STEP_CLR) ;
      STEP_CNT = 0 ;
      if ((MONITOR.inst != INST_MON)&&(MONITOR.inst != INST_PC)){
        INST_CNT++ ;
      }
      return ;
    }
   
    STEP_CNT++ ;
  }
}


void insert_inst(uint8_t opcode, bool process=true){
  DATA.write(opcode) ;
  MONITOR.inst = opcode ;
  CTRL_OUT.pulse_with_sync(INST_S) ;
  DATA.reset() ;

  if (process){
    process_inst(false) ;        
  }
}


void monitor_sample(bool pc_only=false){
  uint8_t inst = MONITOR.inst ;
  insert_inst(pc_only ? INST_PC : INST_MON) ;
  // Replace original instruction
  insert_inst(inst, false) ;
}


void reset6502(PROG *prog, uint16_t force_start_addr=0x00){
  // Clear step counter and program counter
  CTRL_OUT.pulse(STEP_CLR) ;
  CTRL_OUT.pulse(PC_CLR) ;
  // Reset latches
  CLK_sync.pulse() ;

  monitor_sample() ;
  monitor_trace("INIT  ->") ;
  
  // Initialize INST register to RST1
  insert_inst(INST_RST1) ;

  Serial.print(F("- Loading program to RAM...")) ;
  CTRL_OUT.pulse(STEP_CLR) ;
  CTRL_OUT.pulse(PC_CLR) ;
  // Load the program to RAM
  for (int data = prog->get_next_byte() ; data != -1 ; data = prog->get_next_byte()){
    DATA.write(data) ;
    PC_e.toggle() ;     
    CTRL_OUT.pulse_with_sync(RAM_S) ;
    PC_e.toggle() ;
    DATA.reset() ;
    CTRL_OUT.pulse_with_sync(PC_UP) ;
  }        
  Serial.println(F("done")) ;
  Serial.print(F("LOAD  -> ")) ;
  Serial.print(prog->len()) ;
  Serial.println(F(" program bytes loaded")) ;
  
  // Print program info
  prog->describe() ;
  Serial.println() ;

  // Now that program is transfered, install vectors in controller
  VECTORS.set_reset(force_start_addr ? force_start_addr : prog->start_addr()) ;
  VECTORS.set_int(prog->int_addr()) ;
  VECTORS.set_nmi(prog->nmi_addr()) ;

  CTRL_OUT.pulse(STEP_CLR) ;
  insert_inst(INST_RST2) ;

  // We must place another instruction here because RST2 doesn't load the next instruction.
  insert_inst(INST_NOP, false) ;

  monitor_sample() ;
  monitor_trace("RESET ->") ;
  Serial.println(F("---")) ;
}


void process_interrupt(uint8_t opcode){   
  uint8_t inst = MONITOR.inst ;
  monitor_sample() ;
  monitor_trace("INTR  ->") ; 
  insert_inst(opcode, false) ;
  
  DATA.write(opcode) ;        // Enable opcode onto the data bus
  process_inst(false, 2) ;    // The opcode it still on the data bus, the next 3 (0, 1, 2) steps of fetch() will store it to EAl
  DATA.reset() ;              // Reset the data bus
  process_inst(false) ;       // Finish the instruction

  monitor_sample() ;
  monitor_trace("      <-") ;
  insert_inst(inst, false) ;
}


void loop(){
  // Start processing instructions.
  uint16_t prev_pc = 0xFFFF ;
  while (1) {
    if (HALTED){
      // Infinite loop...
      continue ;
    }
    monitor_sample(true) ;
    if (MONITOR.pc == prev_pc){
      bool done = prog->is_done(MONITOR.pc) ;
      Serial.println(F("---")) ;
      monitor_sample() ;
      monitor_trace("TRAP! ->") ;
      Serial.print(done ? F("\nSUCCESS") : F("\nERROR")) ;
      Serial.print(F(" after ")) ;
      Serial.print(INST_CNT) ;
      Serial.print(F(" instructions ")) ;
      Serial.println(done ? F(":)") : F(":(")) ;
      while (1){} ;
    } 
    prev_pc = MONITOR.pc ;

    /*if (MONITOR.pc == 0x201A){
      DEBUG_MON = true ;
    }
    if (MONITOR.pc > 0x2024){
      DEBUG_MON = false ;
    }*/
  
    if ((MON_EVERY)&&((INST_CNT % MON_EVERY) == 0)){
      monitor_sample() ;
      monitor_trace() ; 
    }
    process_inst() ; 

    if (! DEBUG_STEP){
      if (button_pressed(STEP)){
        //DEBUG_STEP = true ;
        process_interrupt(INST_NMI) ;
      }
    }
  }
}
