#include "addrmodes.h"
#include "ops.h"
#include "utils.h"


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
/* 0 */      brk,  ora,  rst1, rst2,  nop,  ora,  asl,  nop,  php,  ora,  asl,  nop,  nop,  ora,  asl,  nop, /* 0 */
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
/* F */      beq,  sbc,  nop,  nop,  nop,  sbc,  inc,  nop,  sed,  sbc,  nop,  nop,  nop,  sbc,  inc,  nop  /* F */
} ;


unsigned long inst_cnt = 0 ;
void monitor6502(bool idle){
  static char buf[128] ;
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


void process_ctrl(){
    if (! RAM_e.read()){
        uint8_t addr = digitalRead(CTRL_ADDR3) << 3 | digitalRead(CTRL_ADDR2) << 2 | digitalRead(CTRL_ADDR1) << 1 | digitalRead(CTRL_ADDR0) ;  
        // read from vectors or IO
        DATA.write(addr < 0xA ? IO.get_byte(addr) : VECTORS.get_byte(addr)) ;
    }
    else {
        DATA.reset() ;      
    }

    if (! RAM_s.read()){
        // write to vectors or IO
        uint8_t addr = digitalRead(CTRL_ADDR3) << 3 | digitalRead(CTRL_ADDR2) << 2 | digitalRead(CTRL_ADDR1) << 1 | digitalRead(CTRL_ADDR0) ;  
        if (addr < 0xA){
            IO.set_byte(addr, DATA.read()) ;
        }
        else {
            VECTORS.set_byte(addr, DATA.read()) ;
        }
    }
}


unsigned long process_inst(bool debug = false){
    // Update the flags values for use in branch instructions. 
    STATUS.latch() ;
    uint8_t addr_start = 0, op_start = 0 ;
    bool fetch_done = false, addr_done = false ;
    for (int step = 0 ; step < 64 ; step++){
        if (! fetch_done){
            if (fetch(step)){
                if (digitalRead(CTRL)){
                  process_ctrl() ;
                }
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
                if (digitalRead(CTRL)){
                  process_ctrl() ;
                }
                if (debug){
                  step6502("addr", step - addr_start) ;
                }
                continue ;
            }
            addr_done = true ;
            op_start = step ;
        }
        
        func6502 f = pgm_read_word(&(optable[INST])) ;
        if (f(step - op_start)){
            if (digitalRead(CTRL)){
              process_ctrl() ;
            }
            if (debug){
              step6502("oper", step - op_start) ;
            }
            continue ;
        }
        // Make sure we reset the bus in case we where driving it. 
        process_ctrl() ;
        
        inst_cnt++ ;
        return inst_cnt ;
    }

    return inst_cnt ;
}


void reset6502(PROG *prog){
    // Install vectors in controller
    Serial.println(F("Starting reset sequence...")) ;
    VECTORS.set_reset(prog->start_addr()) ;
    VECTORS.set_int(prog->int_addr()) ;
    VECTORS.set_nmi(prog->nmi_addr()) ;
    
    inst_cnt = 0 ;
    PC_clr.pulse() ;
    DATA.write(0x02) ; // RST instruction
    PC_e.toggle() ;
    RAM_s.pulse() ;
    PC_e.toggle() ;
    DATA.reset() ;
    process_inst() ;

    Serial.println(F("- Loading program to RAM...")) ;
    PC_clr.pulse() ;
    for (int i = 0 ; i < prog->len() ; i++){
        byte inst = prog->get_byte(i) ;
        DATA.write(inst) ;
        PC_e.toggle() ; 
        RAM_s.pulse() ;
        PC_e.toggle() ;
        DATA.reset() ;
        PC_up.pulse() ;
    }
        
    Serial.print(F("LOAD  -> ")) ;
    Serial.print(prog->len()) ;
    Serial.println(F(" program bytes loaded")) ;

    DATA.write(0x03) ; // RST2 instruction
    PC_e.toggle() ;
    RAM_s.pulse() ;
    PC_e.toggle() ;
    DATA.reset() ;
    process_inst() ;
    
    Serial.print(F("RESET -> ")) ;
    monitor6502(true) ;
    Serial.println() ;
    Serial.println(F("---")) ;
}
