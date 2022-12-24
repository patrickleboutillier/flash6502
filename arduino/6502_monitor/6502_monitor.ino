#include "Extension.h"
#include "BUS.h"
#include "CTRLSIG.h"
#include "ALU.h"
#include "STATUS.h"
#include "VECTORS.h"
#include "IO.h"

// Push button
#define STEP A6         // push button
#define CTRL 12         // Activate controller for vectors and IO
#define CTRL_ADDR0 A0
#define CTRL_ADDR1 A1
#define CTRL_ADDR2 A2
#define CTRL_ADDR3 A3

BUS DATA(9, 8, 7, 6, 5, 4, 3, 2) ;
CTRLSIG PC_clr(NULL, 11) ;
CTRLSIG CLK_async(NULL, 10, true) ;
CTRLSIG STEP_clr(NULL, 13, true) ;

Extension E1(1, "X, Y, ACC, ADDRl") ;
CTRLSIG X_e(&E1, 12, true), X_s(&E1, 11), Y_e(&E1, A0, true), Y_s(&E1, A1) ;
CTRLSIG ACC_s(&E1, 9), ACC_e(&E1, 10, true) ;
CTRLSIG SP_down(&E1, 8, true), SP_s(&E1, 7, true), SP_e(&E1, 6, true), EAl_s(&E1, 5), 
  PC_up(&E1, 4, true), PC_e(&E1, 3, true) ;

Extension E2(2, "ALU, RAM") ;
CTRLSIG A_s(&E1, A2) ;
ALU_OP ALU_op(new CTRLSIG(&E2, 8), new CTRLSIG(&E2, 7), new CTRLSIG(&E2, 6), new CTRLSIG(&E2, 5)) ; 
CTRLSIG ALU_e(&E2, 4, true) ;
CTRLSIG B_s(&E2, 3) ;
CTRLSIG INST_s(&E2, 13) ; // TODO: check this, 13 maybe flaky w/LED
CTRLSIG Al2D_e(&E1, A3, true), Ah2D_e(&E2, 2, true) ;
CTRLSIG EAl_e(&E1, 2, true), PCl_s(&E1, 13, true) ;
CTRLSIG RAM_s(&E2, A2, true), RAM_e(&E2, A3, true) ;
CTRLSIG EAh_e(&E2, A0, true), EAh_s(&E2, A1) ; 

Extension E3(3, "STATUS, ADDRh") ;
CTRLSIG ST_s(&E3, 2) ;
CTRLSIG ST_NZ_s(&E3, 7), ST_V_s(&E3, 6), ST_C_s(&E3, 5), ST_ALU_C_s(&E3, 4) ;
CTRLSIG ST_ALU_C_from_C(&E3, 3) ;
CTRLSIG ST_src(&E3, 8, true) ;
CTRLSIG ST_e(&E3, 9, true) ;
CTRLSIG PCh_s(&E3, 10, true), ST_bi(&E3, 11), ST_I_s(&E3, 13) ; 
STATUS STATUS(&E3, A0, A1, A2, A3, 12) ;

VECTORS VECTORS ;
IO IO ;

bool DEBUG_MON = false ;
bool DEBUG_STEP = false ;
#define MON_EVERY 1000

byte INST = 0 ;


#include "PROG.h"
#include "fake6502.h"
#include "PROGRAMS.h"


// Program to run
PROG *prog = &progTestSuite ;

  
void setup() {
  // Faster analog reads
  ADCSRA = (ADCSRA & 0b11111000) | 0b100 ;

  Serial.begin(115200) ;
  Serial.println(F("Starting Flash6502.")) ;
  Serial.print(CTRLSIG::count()) ;
  Serial.println(F(" control signals defined.")) ;
  pinMode(CTRL, INPUT) ;

  DATA.setup() ;
  PC_clr.setup() ;
  CLK_async.setup() ;
  STEP_clr.setup() ;
  
  X_e.setup() ; X_s.setup() ; Y_e.setup() ; Y_s.setup() ;
  ACC_s.setup() ; ACC_e.setup() ;
  SP_down.setup() ; SP_s.setup() ; SP_e.setup() ; EAl_s.setup() ; 
  PC_up.setup() ; PC_e.setup() ;
  A_s.setup() ;

  // CTRL ROM 3
  /* ALU_op.setup() ;
  ALU_e.setup() ;
  B_s.setup() ;
  ST_e.setup() ;
  ST_src.setup() ; */

  INST_s.setup() ;
  Al2D_e.setup() ; Ah2D_e.setup() ;
  EAl_e.setup() ; PCl_s.setup() ;
  RAM_s.setup() ; RAM_e.setup() ;
  
  ST_s.setup() ;
  ST_NZ_s.setup() ; ST_V_s.setup() ; ST_C_s.setup() ; ST_ALU_C_s.setup() ; ST_I_s.setup() ; ST_bi.setup() ;
  ST_ALU_C_from_C.setup() ;

  PCh_s.setup() ; EAh_e.setup() ; EAh_s.setup() ;
  STATUS.setup() ;
  
  //CTRLSIG::check() ;
  
  prog->describe() ;
  Serial.println() ;
  reset6502(prog) ;
}


// See simulator main while loop
void loop(){
  // Start processing instructions.
  uint16_t prev_pc = 0xFFFF ;
  while (1) {
      uint16_t pc = get_pc() ;
      if (pc == prev_pc){
          bool done = prog->is_done(pc) ;
          Serial.print(F("---\nTRAP! -> ")) ;
          monitor6502(true) ; 
          Serial.println(done ? F("\nSUCCESS :)") : F("\nERROR :(")) ;
          while (1){} ;
      } 
      prev_pc = pc ;

      //if (pc == 0x09F3){
      //  DEBUG_STEP = true ;
      //  DEBUG_MON = true ;
      //}
      
      if (((inst_cnt % MON_EVERY) == 0)||(DEBUG_MON)){
        monitor6502(true) ; Serial.println() ;
      }
      process_inst(0, 0xFF, DEBUG_STEP) ; 

      if (! DEBUG_STEP){
        if (analog_button_pressed(STEP)){
          //DEBUG_STEP = true ;
          //DEBUG_MON = true ;
          process_interrupt(INST_IRQ) ;
        }
      }
  }
}
