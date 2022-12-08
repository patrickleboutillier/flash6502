uint16_t get_ea() ;

#include "addrmodes.h"
#include "ops.h"


void monitor6502(bool idle) ;

  
uint8_t stp(uint8_t step) {
  HALTED = true ;
  Serial.println(F("HALT  -> System halted by STP instruction.")) ;
  Serial.print(F("HALT  -> ")) ;
  monitor6502(true) ;
  Serial.println() ;
  Serial.println() ;
  return 0 ;  
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
/* F */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx  /* F */
} ;


PROGMEM const func6502 optable[256] = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |      */
/* 0 */      brk,  ora,  rst1, slo,  nop,  ora,  asl,  slo,  php,  ora,  asl,  nop,  nop,  ora,  asl,  slo, /* 0 */
/* 1 */      bpl,  ora,  nop,  slo,  nop,  ora,  asl,  slo,  clc,  ora,  nop,  slo,  nop,  ora,  asl,  slo, /* 1 */
/* 2 */      jsr,  and_, nop,  rla,  bit_,  and_,  rol,  rla,  plp,  and_,  rol,  nop,  bit_,  and_,  rol,  rla, /* 2 */
/* 3 */      bmi,  and_, nop,  rla,  nop,  and_,  rol,  rla,  sec,  and_,  nop,  rla,  nop,  and_,  rol,  rla, /* 3 */
/* 4 */      rti,  eor,  nop,  sre,  nop,  eor,  lsr,  sre,  pha,  eor,  lsr,  nop,  jmp,  eor,  lsr,  sre, /* 4 */
/* 5 */      bvc,  eor,  nop,  sre,  nop,  eor,  lsr,  sre,  cli_,  eor,  nop,  sre,  nop,  eor,  lsr,  sre, /* 5 */
/* 6 */      rts,  adc,  nop,  rra,  nop,  adc,  ror,  rra,  pla,  adc,  ror,  nop,  jmp,  adc,  ror,  rra, /* 6 */
/* 7 */      bvs,  adc,  nop,  rra,  nop,  adc,  ror,  rra,  sei_,  adc,  nop,  rra,  nop,  adc,  ror,  rra, /* 7 */
/* 8 */      nop,  sta,  nop,  sax,  sty,  sta,  stx,  sax,  dey,  nop,  txa,  nop,  sty,  sta,  stx,  sax, /* 8 */
/* 9 */      bcc,  sta,  nop,  nop,  sty,  sta,  stx,  sax,  tya,  sta,  txs,  nop,  nop,  sta,  nop,  nop, /* 9 */
/* A */      ldy,  lda,  ldx,  lax,  ldy,  lda,  ldx,  lax,  tay,  lda,  tax,  nop,  ldy,  lda,  ldx,  lax, /* A */
/* B */      bcs,  lda,  nop,  lax,  ldy,  lda,  ldx,  lax,  clv,  lda,  tsx,  lax,  ldy,  lda,  ldx,  lax, /* B */
/* C */      cpy,  cmp,  nop,  dcp,  cpy,  cmp,  dec,  dcp,  iny,  cmp,  dex,  nop,  cpy,  cmp,  dec,  dcp, /* C */
/* D */      bne,  cmp,  nop,  dcp,  nop,  cmp,  dec,  dcp,  cld,  cmp,  nop,  stp,  nop,  cmp,  dec,  dcp, /* D */
/* E */      cpx,  sbc,  nop,  isb,  cpx,  sbc,  inc,  isb,  inx,  sbc,  nop,  sbc,  cpx,  sbc,  inc,  isb, /* E */
/* F */      beq,  sbc,  nop,  isb,  nop,  sbc,  inc,  isb,  sed,  sbc,  nop,  isb,  nop,  sbc,  inc,  isb  /* F */
} ;


uint16_t get_pc(){
  PC_e.toggle() ; 
  Al2D_e.toggle() ;
  uint16_t pc = DATA.read() ;
  Al2D_e.toggle() ; 
  Ah2D_e.toggle() ;
  pc |= DATA.read() << 8 ;
  Ah2D_e.toggle() ; 
  PC_e.toggle() ;   
  return pc ;  
}


void set_pc(uint16_t pc){
  DATA.write(pc >> 8) ;
  PCh_s.pulse() ;
  DATA.reset() ;
  DATA.write(pc & 0xFF) ;
  PCl_s.pulse() ;
  DATA.reset() ;
}

  
uint16_t get_ea(){
  EAl_e.toggle() ; Al2D_e.toggle() ;
  uint16_t ea = DATA.read() ;
  EAl_e.toggle() ; Al2D_e.toggle() ; 
  EAh_e.toggle() ; Ah2D_e.toggle() ;
  ea |= DATA.read() << 8 ;
  EAh_e.toggle() ; Ah2D_e.toggle() ;   
  return ea ; 
}


uint16_t get_sp(){
  SP_e.toggle() ; 
  Al2D_e.toggle() ;
  uint16_t sp = DATA.read() ;
  Al2D_e.toggle() ; 
  Ah2D_e.toggle() ;
  sp |= DATA.read() << 8 ;
  Ah2D_e.toggle() ; 
  SP_e.toggle() ; 
  return sp ;  
}


uint8_t get_acc(){
  ACC_e.toggle() ;
  uint8_t acc = DATA.read() ;
  ACC_e.toggle() ; 
  return acc ;  
}


uint8_t get_x(){
  X_e.toggle() ;
  uint8_t x = DATA.read() ;
  X_e.toggle() ; 
  return x ;  
}


uint8_t get_y(){
  Y_e.toggle() ;
  uint8_t y = DATA.read() ;
  Y_e.toggle() ; 
  return y ;  
}


uint8_t get_status(){
  ST_e.toggle() ;
  uint8_t status = DATA.read() ;
  ST_e.toggle() ;
  return status ;
}


uint8_t set_status(uint8_t s){
  DATA.write(s) ;
  ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ;
  ST_s.pulse() ;
  ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ;
  DATA.reset() ;
}


unsigned long inst_cnt = 0 ;
void monitor6502(bool idle){
  static char buf[128] ;
  // TODO: use sprintf here, add EA
  sprintf(buf, "INST:0x%02X", INST) ;
  Serial.print(buf) ;
  if (idle){
      sprintf(buf, "  PC:0x%04X  EA:0x%04X  SP:0x%04X  STATUS:0x%02X  ACC:%3u  X:%3u  Y:%3u %8lu",
        get_pc(), get_ea(), get_sp(), get_status(), get_acc(), get_x(), get_y(), inst_cnt) ;
      Serial.print(buf) ;
  }
}


void step6502(const char *msg, int step, bool idle = false){
  Serial.print(F("STEP  -> ")) ;
  monitor6502(idle) ;
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
  while (! STEP_button_pressed()){} ;
}



unsigned long inst6502(bool debug = false){
    // Update the flags values for use in branch instructions. 
    STATUS.latch() ;
    uint8_t addr_start = 0, op_start = 0 ;
    bool fetch_done = false, addr_done = false, op_done = false ;
    for (int step = 0 ; step < 64 ; step++){
        if (! fetch_done){
            if (fetch(step)){
                if (debug){
                    // step6502("fetch", step) ;
                }
                continue ;
            } 
            fetch_done = true ;
            addr_start = step ;
        }
        if (! addr_done){
            func6502 f = pgm_read_word(&(addrtable[INST])) ;
            if (f(step - addr_start)){
                if (debug){
                  step6502("addr", step - addr_start) ;
                }
                continue ;
            }
            addr_done = true ;
            op_start = step ;
        }
        if (! op_done){
            func6502 f = pgm_read_word(&(optable[INST])) ;
            if (f(step - op_start)){
                if (debug){
                  step6502("oper", step - op_start) ;
                }
                continue ;
            }
            inst_cnt++ ;
            return inst_cnt ;
        }
    }

    return inst_cnt ;
}


void load6502(uint8_t prog[], int prog_len, Extension *e = NULL){
    PC_clr.pulse() ;

    for (int i = 0 ; i < prog_len ; i++){
        byte inst = (e == NULL ? prog[i] : e->pgm_read_byte_(i)) ;
        DATA.write(inst) ;
        PC_e.toggle() ; 
        RAM_s.pulse() ;
        PC_e.toggle() ;
        //step6502("load", i) ;
        DATA.reset() ;
        PC_up.pulse() ;
    }

    Serial.print(prog_len) ;
    Serial.println(F(" program bytes loaded starting at address 0x0000")) ;
    Serial.print(F("LOAD  -> ")) ;
    monitor6502(true) ;
    Serial.println() ;
    PC_clr.pulse() ;
}


void reset6502(uint8_t prog[], int prog_len, uint16_t pc, Extension *e = NULL){
    inst_cnt = 0 ;
    PC_clr.pulse() ;
    DATA.write(0x02) ; // RST instruction
    PC_e.toggle() ;
    RAM_s.pulse() ;
    PC_e.toggle() ;
    DATA.reset() ;
    // Reset step/phase to 0 and run the instruction.
    inst6502(false) ;
    PC_clr.pulse() ;
    Serial.print(F("RESET -> ")) ;
    monitor6502(true) ;
    Serial.println() ;

    load6502(prog, prog_len, e) ;
    if (pc != 0){
      set_pc(pc) ;
    }
}
