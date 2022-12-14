#include "Extension.h"
#include "BUS.h"
#include "CTRLSIG.h"
#include "ALU.h"
#include "STATUS.h"
#include "VECTORS.h"
#include "IO.h"

// Push button
#define STEP 10         // push button
#define CTRL 12         // Activate controller for vectors and IO
#define CTRL_ADDR0 A0
#define CTRL_ADDR1 A1
#define CTRL_ADDR2 A2
#define CTRL_ADDR3 A3

BUS DATA(9, 8, 7, 6, 5, 4, 3, 2) ;
CTRLSIG PC_clr(NULL, 11) ;

Extension E1(1, "X, Y, ACC, ADDRl") ;
CTRLSIG X_e(&E1, 12, true), X_s(&E1, 11), Y_e(&E1, A0, true), Y_s(&E1, A1) ;
CTRLSIG ACC_s(&E1, 9), ACC_e(&E1, 10, true) ;
CTRLSIG SP_down(&E1, 8, true), SP_s(&E1, 7, true), SP_e(&E1, 6, true), EAl_s(&E1, 5), 
  PC_up(&E1, 4, true), PC_e(&E1, 3, true) ;

Extension E2(2, "ALU, RAM") ;
CTRLSIG A_s(&E2, 9) ;
ALU_OP ALU_op(new CTRLSIG(&E2, 8), new CTRLSIG(&E2, 7), new CTRLSIG(&E2, 6), new CTRLSIG(&E2, 5)) ; 
CTRLSIG ALU_e(&E2, 4, true) ;
CTRLSIG B_s(&E2, 3) ;
CTRLSIG INST_s(&E2, A0) ;
CTRLSIG Al2D_e(&E2, 10, true), Ah2D_e(&E2, 2, true) ;
CTRLSIG EAl_e(&E2, 12, true), PCl_s(&E2, 11, true) ;
CTRLSIG RAM_s(&E2, A2, true), RAM_e(&E2, A3, true) ;

Extension E3(3, "STATUS, ADDRh") ;
CTRLSIG ST_s(&E3, 2) ;
CTRLSIG ST_NZ_s(&E3, 7), ST_V_s(&E3, 6), ST_C_s(&E3, 5), ST_ALU_C_s(&E3, 4) ;
CTRLSIG ST_ALU_C_from_C(&E3, 3) ;
CTRLSIG ST_src(&E3, 8, true) ;
CTRLSIG ST_e(&E3, 9, true) ;
CTRLSIG PCh_s(&E3, 10, true), EAh_e(&E3, 11, true), EAh_s(&E3, 12) ; 
STATUS STATUS(&E3, A0, A1, A2, A3) ;

VECTORS VECTORS ;
IO IO ;

#define START_PC 0
bool DEBUG_MON = false ;
bool DEBUG_STEP = false ;

byte STEP_clr = 1 ;
byte INST = 0 ;


bool STEP_button_pressed() ;
#include "PROG.h"
#include "fake6502.h"
#include "PROGRAMS.h"


// Program to run
PROG *prog = &progHello ; // &progTestSuite ;

  
void setup() {
  Serial.begin(115200) ;
  Serial.println(F("Starting Flash6502.")) ;
  //Serial.print(CTRLSIG::count()) ;
  //Serial.println(F(" control signals defined.")) ;
  pinMode(CTRL, INPUT) ;

  DATA.setup() ;
  PC_clr.setup() ;
  
  X_e.setup() ; X_s.setup() ; Y_e.setup() ; Y_s.setup() ;
  ACC_s.setup() ; ACC_e.setup() ;
  SP_down.setup() ; SP_s.setup() ; SP_e.setup() ; EAl_s.setup() ; 
  PC_up.setup() ; PC_e.setup() ;
  
  A_s.setup() ;
  ALU_op.setup() ;
  ALU_e.setup() ;
  B_s.setup() ;
  INST_s.setup() ;
  Al2D_e.setup() ; Ah2D_e.setup() ;
  EAl_e.setup() ; PCl_s.setup() ;
  RAM_s.setup() ; RAM_e.setup() ;
  
  ST_s.setup() ;
  ST_NZ_s.setup() ; ST_V_s.setup() ; ST_C_s.setup() ; ST_ALU_C_s.setup() ;
  ST_ALU_C_from_C.setup() ;
  ST_src.setup() ;
  ST_e.setup() ;
  PCh_s.setup() ; EAh_e.setup() ; EAh_s.setup() ;
  STATUS.setup() ;
  CTRLSIG::check() ;
  
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

      // step6502("inst", -1, true) ;
      if (((inst_cnt % 1000) == 0)||(DEBUG_MON)){
        monitor6502(true) ; Serial.println() ;
      }
      process_inst(DEBUG_STEP) ; 
  }
}


#define DEBOUNCE_DELAY_MS 50

bool STEP_button_pressed(){
  static bool button_state = HIGH ;
  static bool last_button_state = button_state ;
  static unsigned long last_debounce_time = 0 ;
  bool ret = 0 ;
  int reading = digitalRead(STEP) ;
  
  if (reading != last_button_state) {
    last_debounce_time = millis() ;
  }
  
  if ((millis() - last_debounce_time) > DEBOUNCE_DELAY_MS){
    if (reading != button_state){
      button_state = reading ;
      if (button_state == HIGH){
        ret = 1 ;
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  last_button_state = reading ;
   
  return ret ;
}


void step(){
   Serial.println(F("\nSTEP:")) ;
   while (! STEP_button_pressed()){} ; 
}
