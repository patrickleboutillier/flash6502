// Some globals...
unsigned long INST_CNT = 0 ;
uint8_t STEP_CNT = 0 ;
bool QUIET = true ;

// Push buttons for interrupts and stepping 
#define NMI   A5
#define IRQ   A4

// Some useful instruction opcodes and other defines
#define INST_RST1         0x2F
#define INST_RST2         0x3F
#define INST_NOP          0xEA
#define INST_IRQ          0xFF
#define INST_NMI          0xFB
#define MAX_STEP          64

#include "DATA.h"
#include "VECTORS.h"
void halt6502() ;
#include "IO.h"
#include "CTRL.h"
#include "PROG.h"
#include "TEST.h"

// Debug and optimization stuff
#define ENABLE_INTERRUPTS       0       
#define DEBOUNCE_INTERRUPTS     0
#define ENABLE_MONITORING       0
#define ENABLE_TRAP_DETECTION   0
#define ENABLE_VERBOSITY        0

DATA DATA ;              // 9, 8, 7, 6, 5, 4, 3, 2
VECTORS VECTORS ;
IO IO ;
CTRL CTRL(&DATA, &VECTORS, &IO) ;      // 12, 11, 10, A1


#if ENABLE_MONITORING
  #include "MONITOR.h"
  MONITOR MONITOR(&DATA) ;
  
   // We use these buttons also to enable monitoring and to do stepping. 
  #define STEP  NMI 
  #define MON   IRQ
  
  // Some globals useful for debugging.
  bool DEBUG_MON = false ;
  bool DEBUG_STEP = false ;
#endif


void setup() {
  // Faster analog reads
  ADCSRA = (ADCSRA & 0b11111000) | 0b100 ;

  Serial.begin(9600) ;
  #define SERIAL_TIMEOUT 1000
  Serial.setTimeout(SERIAL_TIMEOUT) ;
  // Send null byte to indicate we have finished booting, in case a loader is present.
  Serial.write(0) ;
  Serial.println(F("Starting Flash6502")) ;  

  PROG *prog = detect_loader() ;

  #if ENABLE_MONITORING
    if (! digitalRead(MON)){
      Serial.println(F("IRQ/MON button held down, entering monitor mode.\n")) ;
      DEBUG_MON = true ;
    }
    if (! digitalRead(STEP)){
      Serial.println(F("NMI/STEP button held down, entering step mode.\n")) ;
      DEBUG_STEP = true ;
      DEBUG_MON = true ;
    }
  #endif
  
  reset6502(prog, 0) ;
}


PROG *detect_loader(){
  // Read the magic number that indicates our loader is present.
  byte magic[3] ;
  int nb = Serial.readBytes(magic, 3) ;
  if ((magic[0] == 0x65)&&(magic[1] == 0x02)){
    IO.set_loader() ;
    if (magic[2] == 0xFF){
      Serial.println(F("Loader detected, program will be requested from loader.")) ;
      return new PROG("@loader") ;
    }
    else {
      Serial.println(F("Loader detected, continuing with built-in test suite.")) ;
    }
  }
  else {
    Serial.println(F("No loader detected, continuing with built-in test suite.")) ;
  }

  QUIET = false ;
  
  return new PROG("TestSuite", test_suite, 14649, true, 0x0400, 0x38A7, 0x3899, 0x3699) ;
}


void reset6502(PROG *prog, uint16_t force_start_addr){
  // Clear step counter and program counter
  CTRL.pulse(STEP_CLR) ;
  CTRL.pulse(PC_CLR) ;
  // Reset latches
  CTRL.pulse_sync() ;

  #if ENABLE_MONITORING
    MONITOR.sample() ;
    MONITOR.trace("INIT  ->") ;
  #endif
  
  // Initialize INST register to RST1
  insert_inst(INST_RST1, true) ;

  #if ENABLE_VERBOSITY
    Serial.print(F("- Loading program to RAM...")) ;
  #endif
  CTRL.pulse(STEP_CLR) ;
  CTRL.pulse(PC_CLR) ;
  // Load the program to RAM
  for (int data = prog->get_next_byte() ; data != -1 ; data = prog->get_next_byte()){
    DATA.write(data) ; 
    CTRL.PC_e_on() ;
    CTRL.pulse_with_sync(RAM_S) ;
    CTRL.PC_e_off() ;
    DATA.reset() ;
    CTRL.pulse_with_sync(PC_UP) ;
  }

  #if ENABLE_VERBOSITY
    Serial.println(F("done")) ;
    Serial.print(F("LOAD  -> ")) ;
    Serial.print(prog->len()) ;
    Serial.println(F(" program bytes loaded")) ;
    
    // Print program info
    prog->describe() ;
    Serial.println() ;
  #endif

  // Now that program is transfered, install vectors in controller
  VECTORS.set_reset(force_start_addr ? force_start_addr : prog->start_addr()) ;
  VECTORS.set_int(prog->int_addr()) ;
  VECTORS.set_nmi(prog->nmi_addr()) ;

  CTRL.pulse(STEP_CLR) ;
  insert_inst(INST_RST2, true) ;

  // We must place another instruction here because RST2 doesn't load the next instruction.
  insert_inst(INST_NOP, false) ;

  #if ENABLE_MONITORING
    MONITOR.sample() ;
    MONITOR.trace("RESET ->") ;
  #endif
  #if ENABLE_VERBOSITY
    Serial.println(F("---")) ;
  #endif
}


void insert_inst(uint8_t opcode, bool process){
  DATA.write(opcode) ;
  #if ENABLE_MONITORING
    MONITOR.set_inst(opcode) ;
  #endif
  CTRL.pulse_with_sync(INST_S) ;
  DATA.reset() ;

  if (process){
    process_inst(false, MAX_STEP) ; 
  }
}


inline void process_inst(bool grab_inst, uint8_t max_step){
  bool prev_ctrl = false ; 
  while (STEP_CNT <= max_step){    
    #if ENABLE_MONITORING
      MONITOR.process(grab_inst) ;
    #endif
    
    if (STEP_CNT > 0){
      // This already happened for step 0 when we called STEP_CLR
      CTRL.pulse(CLK_ASYNC) ; 
      CTRL.pulse_sync() ;  
    }

    if (PINC & 0b100){ // A2, CTRL
      CTRL.process() ;
      prev_ctrl = true ;
    }
    else if (prev_ctrl){
      CTRL.clear_cache() ;
      DATA.reset() ;
    }

    #if ENABLE_MONITORING
      if (DEBUG_MON){
        if (DEBUG_STEP){
          MONITOR.step() ;
        }
        else {
          MONITOR.trace() ;
        }
      }
    #endif

    if (PINC & 0b1000){ // A3, INST_done
      if (grab_inst){
        INST_CNT++ ;
      }
      // Reset step counter.
      CTRL.pulse(STEP_CLR) ;
      CTRL.pulse_sync() ;
      STEP_CNT = 0 ;
      return ;
    }
   
    STEP_CNT++ ;
  }
}


void loop(){
  // Start processing instructions.
  while (1) {
    process_inst(true, MAX_STEP) ;

    #if ENABLE_VERBOSITY
      if ((!QUIET)&&((INST_CNT & 0x3FFF) == 0)){
        #if ENABLE_MONITORING
          MONITOR.sample(true) ; // PC-only monitor
        #endif
        Serial.print(INST_CNT) ;
        Serial.print(" instructions executed (pc:0x") ;
        #if ENABLE_MONITORING
          Serial.print(MONITOR.get_pc(), HEX) ;
        #else
          Serial.print("????") ;
        #endif
        Serial.print(", rate:") ;
        float rate = INST_CNT / (millis() / 1000.0) ;
        Serial.print(rate) ;
        Serial.println(" insts/sec)") ;
      }
    #endif

    #if ENABLE_MONITORING
      #if ENABLE_TRAP_DETECTION
        MONITOR.sample(true) ; // PC-only monitor
    
        // Let's check if the PC has changed 
        if (! MONITOR.pc_changed()){
          bool done = prog->is_done(MONITOR.get_pc()) ;
          Serial.println(F("---")) ;
          MONITOR.sample() ;
          MONITOR.trace("TRAP! ->") ;
          Serial.print(done ? F("\nSUCCESS") : F("\nERROR")) ;
          Serial.print(F(" after ")) ;
          Serial.print(INST_CNT) ;
          Serial.print(F(" instructions ")) ;
          Serial.println(done ? F(":)") : F(":(")) ;
          while (1){} ;
        }
      #endif 
    #endif

    #if ENABLE_INTERRUPTS
      #if DEBOUNCE_INTERRUPTS
        if (button_pressed(NMI)){
          process_interrupt(INST_NMI) ;
        }
        if (button_pressed(IRQ)){
          process_interrupt(INST_IRQ) ;
        }
      #else
        if (! (PINC & 0b00100000)){
          process_interrupt(INST_NMI) ;
        }
        if (! (PINC & 0b00100000)){
          process_interrupt(INST_IRQ) ;
        }
      #endif
    #endif    
  }
}


void process_interrupt(uint8_t opcode){   
  #if ENABLE_MONITORING
    uint8_t inst = MONITOR.get_inst() ;
    MONITOR.sample() ;
    MONITOR.trace("INTR  ->") ; 
  #else
    uint8_t inst = INST_NOP ;
    #if ENABLE_VERBOSITY
      if (! QUIET){
        Serial.println(opcode == INST_NMI ? "NMI" : "IRQ") ;
      }
    #endif
  #endif
  insert_inst(opcode, false) ;
  
  DATA.write(opcode) ;            // Enable opcode onto the data bus
  process_inst(false, 2) ;        // The opcode it still on the data bus, the next 3 (0, 1, 2) steps of fetch() will store it to EAl
  DATA.reset() ;                  // Reset the data bus
  process_inst(false, MAX_STEP) ; // Finish the instruction

  #if ENABLE_MONITORING
    MONITOR.sample() ;
    MONITOR.trace("      <-") ;
  #endif
  insert_inst(inst, false) ;
}


void halt6502(){
  // #IF ENABLE_VERBOSITY
  if (!QUIET){
    Serial.println("HALTED!") ;
    pinMode(LED_BUILTIN, OUTPUT) ;
    digitalWrite(LED_BUILTIN, HIGH) ;
    Serial.print("Duration: ") ;
    Serial.print(millis() / 1000) ;
    Serial.println(" seconds.") ;
  }
  while (1){} ; 
}


////////// Utility functions //////////


bool button_pressed(uint8_t button_pin){
  #define DEBOUNCE_DELAY_MS 50
  static bool button_state = LOW ;
  static bool last_button_state = button_state ;
  static unsigned long last_debounce_time = 0 ;
  bool ret = 0 ;
  bool reading = digitalRead(button_pin) ;
  
  if (reading != last_button_state) {
    last_debounce_time = millis() ;
  }
  
  if ((millis() - last_debounce_time) > DEBOUNCE_DELAY_MS){
    if (reading != button_state){
      button_state = reading ;
      if (button_state == LOW){
        ret = 1 ;
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  last_button_state = reading ;
   
  return ret ;
}
