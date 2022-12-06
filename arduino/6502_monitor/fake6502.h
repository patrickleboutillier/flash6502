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

typedef uint8_t (*func6502)(uint8_t step) ;

PROGMEM const func6502 addrtable[256] = {
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
} ;


PROGMEM const func6502 optable[256] = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |      */
/* 0 */      brk,  ora,  rst,  slo,  nop,  ora,  asl,  slo,  php,  ora,  asl,  nop,  nop,  ora,  asl,  slo, /* 0 */
/* 1 */      bpl,  ora,  nop,  slo,  nop,  ora,  asl,  slo,  clc,  ora,  nop,  slo,  nop,  ora,  asl,  slo, /* 1 */
/* 2 */      jsr,  and_,  nop,  rla,  bit_,  and_,  rol,  rla,  plp,  and_,  rol,  nop,  bit_,  and_,  rol,  rla, /* 2 */
/* 3 */      bmi,  and_,  nop,  rla,  nop,  and_,  rol,  rla,  sec,  and_,  nop,  rla,  nop,  and_,  rol,  rla, /* 3 */
/* 4 */      rti,  eor,  nop,  sre,  nop,  eor,  lsr,  sre,  pha,  eor,  lsr,  nop,  jmp,  eor,  lsr,  sre, /* 4 */
/* 5 */      bvc,  eor,  nop,  sre,  nop,  eor,  lsr,  sre,  cli_,  eor,  nop,  sre,  nop,  eor,  lsr,  sre, /* 5 */
/* 6 */      rts,  adc,  nop,  rra,  nop,  adc,  ror,  rra,  pla,  adc,  ror,  nop,  jmp,  adc,  ror,  rra, /* 6 */
/* 7 */      bvs,  adc,  nop,  rra,  nop,  adc,  ror,  rra,  sei_,  adc,  nop,  rra,  nop,  adc,  ror,  rra, /* 7 */
/* 8 */      nop,  sta,  nop,  sax,  sty,  sta,  stx,  sax,  dey,  nop,  txa,  nop,  sty,  sta,  stx,  sax, /* 8 */
/* 9 */      bcc,  sta,  nop,  nop,  sty,  sta,  stx,  sax,  tya,  sta,  txs,  nop,  nop,  sta,  nop,  nop, /* 9 */
/* A */      ldy,  lda,  ldx,  lax,  ldy,  lda,  ldx,  lax,  tay,  lda,  tax,  nop,  ldy,  lda,  ldx,  lax, /* A */
/* B */      bcs,  lda,  nop,  lax,  ldy,  lda,  ldx,  lax,  clv,  lda,  tsx,  lax,  ldy,  lda,  ldx,  lax, /* B */
/* C */      cpy,  cmp,  nop,  dcp,  cpy,  cmp,  dec,  dcp,  iny,  cmp,  dex,  nop,  cpy,  cmp,  dec,  dcp, /* C */
/* D */      bne,  cmp,  nop,  dcp,  nop,  cmp,  dec,  dcp,  cld,  cmp,  nop,  dcp,  nop,  cmp,  dec,  dcp, /* D */
/* E */      cpx,  sbc,  nop,  isb,  cpx,  sbc,  inc,  isb,  inx,  sbc,  nop,  sbc,  cpx,  sbc,  inc,  isb, /* E */
/* F */      beq,  sbc,  nop,  isb,  nop,  sbc,  inc,  isb,  sed,  sbc,  nop,  isb,  nop,  sbc,  inc,  isb  /* F */
} ;


// TODO: Add PC and SP here?
void step6502(const char *msg, int tick){
  Serial.print(F("STEP  -> ")) ;
  Serial.print(F("INST:0x")) ;
  Serial.print(INST, HEX) ;
  Serial.print(F(" ")) ;
  Serial.print(msg) ;
  Serial.print(F(" ")) ;
  Serial.print(tick) ;
  Serial.println(F("...")) ;
  while (! STEP_button_pressed()){} ;
}


uint16_t get_pc(){
  PC_e.toggle() ; 
  Al2D_e.toggle() ;
  uint8_t sp = DATA.read() ;
  Al2D_e.toggle() ; 
  Ah2D_e.toggle() ;
  sp |= DATA.read() << 8 ;
  Ah2D_e.toggle() ; 
  PC_e.toggle() ;   
  return sp ;  
}


uint8_t get_sp(){
  SP_e.toggle() ; Al2D_e.toggle() ;
  uint8_t sp = DATA.read() ;
  SP_e.toggle() ; Al2D_e.toggle() ; 
  return sp ;  
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


void do_inst(){
    uint8_t addr_start = 0, op_start = 0 ;
    bool fetch_done = false, addr_done = false, op_done = false ;
    for (int step = 0 ; step < 64 ; step++){
        if (! fetch_done){
            if (fetch(step)){
                step6502("fetch", step) ;
                continue ;
            } 
            fetch_done = true ;
            addr_start = step ;
        }
        if (! addr_done){
            func6502 f = pgm_read_word(&(addrtable[INST])) ;
            if (f(step - addr_start)){
                step6502("addr", step - addr_start) ;
                continue ;
            }
            addr_done = true ;
            op_start = step ;
        }
        if (! op_done){
            func6502 f = pgm_read_word(&(optable[INST])) ;
            if (f(step - op_start)){
                step6502("op", step - op_start) ;
                continue ;
            }
            return ;
        }
    }
}


void reset6502(){
    PC_clr.pulse() ;
    DATA.write(0x02) ; // RST instruction
    PC_e.toggle() ;
    RAM_s.pulse() ;
    PC_e.toggle() ;
    DATA.reset() ;
    // Reset step/phase to 0 and run the instruction.
    do_inst() ;
    PC_clr.pulse() ;
    Serial.print(F("RESET -> PC:0x")) ;
    Serial.print(get_pc(), HEX) ;
    Serial.print(F(", SP:0x")) ;
    Serial.print(get_sp(), HEX) ;
    Serial.print(F(", STATUS:0x")) ;
    Serial.println(get_status(), HEX) ;
}


void load6502(uint8_t prog[], int prog_len){
    PC_clr.pulse() ;

    for (int i = 0 ; i < prog_len ; i++){
        DATA.write(prog[i]) ;
        PC_e.toggle() ; 
        RAM_s.pulse() ;
        PC_e.toggle() ;
        step6502("load", i) ;
        DATA.reset() ;
        PC_up.pulse() ;
    }

    PC_clr.pulse() ;
    Serial.print(F("LOAD  -> ")) ;
    Serial.print(prog_len) ;
    Serial.print(F(" bytes loaded starting at address 0x0000 (PC is now 0x")) ;
    Serial.print(get_pc(), HEX) ;
    Serial.print(F(")\n")) ;
}
