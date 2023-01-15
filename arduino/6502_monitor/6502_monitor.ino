#include "Extension.h"
#include "BUS.h"
#include "CTRLSIG.h"
#include "CTRL_OUT.h"
#include "ALU.h"
#include "STATUS.h"
#include "VECTORS.h"

#define SERIAL_TIMEOUT 1000
bool HALTED = false ;
#include "IO.h"


// Push button
#define STEP A0         // push button
#define CTRL A2         // Activate controller for vectors and IO
#define CTRL_ADDR0 A2
#define CTRL_ADDR1 A3
#define CTRL_ADDR2 A6
#define CTRL_ADDR3 A7

BUS DATA ;                    // 9, 8, 7, 6, 5, 4, 3, 2
CTRLSIG CTRL_src(NULL, 13) ;
CTRL_OUT CTRL_OUT ;           // 12, 11, 10

//CTRL1, CTRL2
Extension E1(1, "X, Y, ACC, ADDRl") ;
CTRLSIG X_e(&E1, 12, true), X_s(&E1, 11), Y_e(&E1, A0, true), Y_s(&E1, A1) ;
CTRLSIG ACC_s(&E1, 9), ACC_e(&E1, 10, true) ;
CTRLSIG SP_down(&E1, 8, true), SP_s(&E1, 7, true), SP_e(&E1, 6, true), EAl_s(&E1, 5), 
  PC_up(&E1, 4, true), PC_e(&E1, 3, true) ;
CTRLSIG A_s(&E1, A2) ;
CTRLSIG INST_s(&E1, 0) ; 
CTRLSIG RAM_s(&E1, 1, true) ; 
CTRLSIG EAl_e(&E1, 2, true), PCl_s(&E1, 13, true) ;
CTRLSIG Al2D_e(&E1, A3, true) ;

Extension E2(2, "ALU, RAM") ;
// CTRL3
ALU_OP ALU_op(new CTRLSIG(&E2, 8), new CTRLSIG(&E2, 7), new CTRLSIG(&E2, 6), new CTRLSIG(&E2, 5)) ; 
CTRLSIG ALU_e(&E2, 4, true) ;
CTRLSIG B_s(&E2, 3) ;

Extension E3(3, "STATUS, ADDRh") ;
CTRLSIG ST_src(&E2, 11, true) ;
CTRLSIG ST_e(&E2, 12, true) ;

// CTRL4
CTRLSIG RAM_e(&E3, 13, true) ;
CTRLSIG Ah2D_e(&E3, 11, true) ;
CTRLSIG EAh_e(&E3, 10, true) ;
CTRLSIG EAh_s(&E3, 9) ; 
CTRLSIG PCh_s(&E3, 8, true) ;
STATUS STATUS(&E3, A0, A1, A2, A3, 12) ;

// CTRL5
CTRLSIG ST_bi(&E3, 7) ;
CTRLSIG ST_NZ_s(&E3, 6) ;
CTRLSIG ST_V_s(&E3, 5) ;
CTRLSIG ST_I_s(&E3, 4) ; 
CTRLSIG ST_C_s(&E3, 3) ;
CTRLSIG ST_ALU_C_s(&E3, 2) ;
CTRLSIG ST_ALU_C_from_C(&E3, 0) ;
CTRLSIG ST_clk(&E3, 1, true) ;

VECTORS VECTORS ;
IO IO ;

byte INST = 0 ;
bool INST_done = 0 ; 

#include "PROG.h"
#include "PROGRAMS.h"

// Program to run
PROG *prog = &progTestSuite ;
//PROG *prog = &progStar ;
//PROG *prog = &progHello ;

bool LOADER = false ;
#include "fake6502.h"

  
void setup() {
  // Faster analog reads
  ADCSRA = (ADCSRA & 0b11111000) | 0b100 ;

  Serial.begin(9600) ;
  Serial.setTimeout(SERIAL_TIMEOUT) ;
  // Send null byte to indicate we have finished booting, in case a loader is present.
  Serial.write(0) ;
  Serial.println(F("Starting Flash6502")) ;  
  prog = check_for_loader() ;

  //Serial.print(CTRLSIG::count()) ;
  //Serial.println(F(" control signals defined.")) ;
  pinMode(CTRL, INPUT) ;

  DATA.setup() ;
  CTRL_src.setup() ;
  
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
  
  ST_clk.setup() ;
  ST_NZ_s.setup() ; ST_V_s.setup() ; ST_C_s.setup() ; ST_ALU_C_s.setup() ; ST_I_s.setup() ; ST_bi.setup() ;
  ST_ALU_C_from_C.setup() ;

  PCh_s.setup() ; EAh_e.setup() ; EAh_s.setup() ;
  STATUS.setup() ;
  
  //CTRLSIG::check() ;
  
  if (! digitalRead(STEP)){
    Serial.println(F("STEP button held down, entering step mode.\n")) ;
    DEBUG_STEP = true ;
    DEBUG_MON = true ;
  }
  
  reset6502(prog) ;
  //set_pc(0x059e) ;
}


PROG *check_for_loader(){
  // Read the magic numer that indicates our loader is present.
  byte magic[2] ;
  int nb = Serial.readBytes(magic, 2) ;
  if ((magic[0] == 0x65)&&(magic[1] == 0x02)){
    Serial.println(F("Loader detected, program will be requested from loader.")) ;
    IO.set_loader() ;
    MON_EVERY = 0 ;
    return new PROG("@loader") ;
  }
  else {
    Serial.println(F("No loader detected, continuing with built-in test suite.")) ;
  }
  
  return &progTestSuite ;
}
