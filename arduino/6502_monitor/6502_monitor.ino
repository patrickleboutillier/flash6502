#include "Extension.h"
#include "BUS.h"
#include "CTRLSIG.h"
#include "ALU.h"
#include "STATUS.h"


// Push button
#define STEP 10

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

#define START_PC 0
bool DEBUG_MON = false ;
bool DEBUG_STEP = false ;

bool HALTED = false ;
byte STEP_clr = 1 ;
byte INST = 0 ;


bool STEP_button_pressed() ;
#include "fake6502.h"
#include "PROGRAMS.h"


void setup() {
  Serial.begin(115200) ;
  Serial.println(F("Starting Flash6502.")) ;
  //Serial.print(CTRLSIG::count()) ;
  //Serial.println(F(" control signals defined.")) ;

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
  
  //reset() ;
  //test_ram() ;
  
  //reset6502(prog42, sizeof(prog42), START_PC) ;
  reset6502(NULL, 14625, START_PC, &E1) ;
  // load6502(prog42, sizeof(prog42)) ;

  //test() ;

  // Serial.println(F("DONE")) ;
}

void loop(){
  if (! HALTED){
    //if (get_pc() == 0x1814){
    //  DEBUG_STEP = true ;
    //}
    
    // step6502("inst", -1, true) ;
    if (((inst_cnt % 1000) == 0)||(DEBUG_MON)){
      monitor6502(true) ; Serial.println() ;
    }
    inst6502(DEBUG_STEP) ;
  }
  else {
    while (! STEP_button_pressed()){} ;
    HALTED = false ;
    reset6502(prog42, sizeof(prog42), START_PC) ;
  }
  
  //byte data = DATA.read() ;
  //Serial.print("DATA:0x") ;
  //Serial.println(data, HEX) ; 
}

void test(){
  for (int a = 0 ; a < 256 ; a++){
    Serial.println(a) ;
    test_ror(a, a) ;
    for (int b = 0 ; b < 256 ; b++){
      test_adc(a << 8 | b, a, b) ;      
    }
  }

  //test_adc(1, 20, 22) ;
  //test_adc(2, 75, 58) ;
  //test_adc(3, 140, 140) ;
  //test_adc(4, 20, 22) ;
} 


void test_ram(){
  for (int i = 0 ; i < 10000 ; i++){
    uint8_t data = rand() & 0xFF ;
    uint16_t addr = rand() & 0xFFFF ;
    
    DATA.write(addr >> 8) ;
    EAh_s.pulse() ;
    DATA.reset() ;
    DATA.write(addr & 0xFF) ;
    EAl_s.pulse() ;   
    DATA.reset() ;
  
    EAh_e.toggle() ; EAl_e.toggle() ;
    DATA.write(data) ;
    RAM_s.pulse() ;
    DATA.reset() ;
    RAM_e.toggle() ;
    ACC_s.pulse() ;
    RAM_e.toggle() ;
    EAh_e.toggle() ; EAl_e.toggle() ;
  
    // Get data from ACC
    ACC_e.toggle() ;
    byte data2 = DATA.read() ;
    ACC_e.toggle() ;
    EXPECT_EQ("RAM", i, data, data2) ;
  }
}


void reset(){
  // Clear flags
  set_status(0) ;
  // Clear ALU carry
  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ;
  ST_s.pulse() ;
  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ;  
  Serial.print("RESET -> STATUS:0x") ;
  Serial.print(get_status(), HEX) ;
  
  // Clear and initialise SP, data bus should be reset
  SP_s.pulse() ;
  SP_down.pulse() ;
  SP_down.pulse() ;
  SP_down.pulse() ;
  
  Serial.print("  SP:0x") ;
  SP_e.toggle() ; Al2D_e.toggle() ;
  Serial.print(DATA.read(), HEX) ;
  SP_e.toggle() ; Al2D_e.toggle() ; 
  Serial.println() ;
}


int calc_v(uint8_t a, uint8_t b, uint16_t res){
    return ((((a & 0xFF)^(res & 0xFF)) & ((b & 0xFF)^(res & 0xFF))) >> 7) & 1 ;
}

void EXPECT_EQ(const char *msg, int test, byte a, byte b){
  if (a != b){
    Serial.print("Test ") ;
    Serial.print(test) ;
    Serial.print(" -> ") ;
    Serial.print(msg) ;
    Serial.print(": ") ;
    Serial.print(a, BIN) ;
    Serial.print(" != ") ;
    Serial.print(b, BIN) ;
    Serial.print("\n") ;
  }
}

/*
void test_adc(int nb, uint8_t a, uint8_t b){
  ALU_op = ALU_ADC ;
  uint8_t status = get_status() ;
  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ;
  ST_s.pulse() ;
  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ;
  uint8_t ci = status & 0b00000001 ;
  DATA.write(a) ;
  A_s.pulse() ;
  DATA.reset() ;
  DATA.write(b) ;
  B_s.pulse() ;
  DATA.reset() ;
  ALU_e.toggle() ; 
  ST_C_s.toggle() ; ST_V_s.toggle(); ST_NZ_s.toggle() ;
  ACC_s.pulse() ; ST_s.pulse() ;
  ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle(); ST_NZ_s.toggle() ;
  ACC_e.toggle() ;
  uint8_t res = DATA.read() ;
  ACC_e.toggle() ;
  status = get_status() ;
  uint16_t exp = a + b + ci ;
  EXPECT_EQ("ADC", nb, res, exp & 0xFF) ;
  EXPECT_EQ("ADC.C", nb, status & 1, (exp >> 8) & 1) ;
  EXPECT_EQ("ADC.N", nb, (status >> 7) & 1, (exp & 0b10000000 ? 1 : 0)) ;
  EXPECT_EQ("ADC.Z", nb, (status >> 1) & 1, ((exp & 0xFF) == 0 ? 1 : 0)) ;
  EXPECT_EQ("ADC.V", nb, (status >> 6) & 1, calc_v(a, b, exp)) ;
}
*/

void test_adc(int nb, uint8_t a, uint8_t b){
  uint8_t ci = get_status() & 0b00000001 ;
  // Place a in ACC
  DATA.write(a) ;
  ACC_s.pulse() ;
  DATA.reset() ;
  // Place b in B
  DATA.write(b) ;
  B_s.pulse() ;
  DATA.reset() ;
  
  // Run all steps in adc()...
  int step = 0 ;
  while (adc(step)){
    step++ ;
  }

  ACC_e.toggle() ;
  uint8_t res = DATA.read() ;
  ACC_e.toggle() ;
  byte status = get_status() ;
  uint16_t exp = a + b + ci ;
  EXPECT_EQ("ADC", nb, res, exp & 0xFF) ;
  EXPECT_EQ("ADC.C", nb, status & 1, (exp >> 8) & 1) ;
  EXPECT_EQ("ADC.N", nb, (status >> 7) & 1, (exp & 0b10000000 ? 1 : 0)) ;
  EXPECT_EQ("ADC.Z", nb, (status >> 1) & 1, ((exp & 0xFF) == 0 ? 1 : 0)) ;
  EXPECT_EQ("ADC.V", nb, (status >> 6) & 1, calc_v(a, b, exp)) ;
}

void test_ror(int nb, uint8_t b){
  ALU_op = ALU_ROR ;
  uint8_t status = get_status() ;
  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ;
  ST_s.pulse() ;
  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ;
  uint8_t ci = status & 0b00000001 ;
  DATA.write(b) ;
  B_s.pulse() ;
  DATA.reset() ;
  ALU_e.toggle() ; 
  ST_C_s.toggle() ; ST_V_s.toggle(); ST_NZ_s.toggle() ;
  ACC_s.pulse() ; ST_s.pulse() ;
  ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle(); ST_NZ_s.toggle() ;
  ACC_e.toggle() ;
  uint8_t res = DATA.read() ;
  ACC_e.toggle() ;
  status = get_status() ;
  uint16_t exp = ci << 7 | b >> 1 ;
  EXPECT_EQ("ROR", nb, res, exp & 0xFF) ;
  EXPECT_EQ("ROR.C", nb, status & 1, b & 1) ;
  EXPECT_EQ("ROR.N", nb, (status >> 7) & 1, (exp & 0b10000000 ? 1 : 0)) ;
  EXPECT_EQ("ROR.Z", nb, (status >> 1) & 1, ((exp & 0xFF) == 0 ? 1 : 0)) ;
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
