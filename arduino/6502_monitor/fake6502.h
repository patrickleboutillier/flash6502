#include "utils.h"

#define INST_PC      0x0F
#define INST_MON     0x1F
#define INST_RST1    0x2F
#define INST_RST2    0x3F
#define INST_NOP     0xEA
#define INST_IRQ     0xFF
#define INST_NMI     0xFB


// Some globals useful for debugging.
int MON_EVERY = 10000 ; 
bool DEBUG_MON = false ;
bool DEBUG_STEP = false ;
unsigned long INST_CNT = 0 ;
uint8_t STEP_CNT = 0 ;

struct {
    uint16_t pc, ea, prev_pc ;
    uint8_t inst, sp, acc, x, y, status, prev_inst ;
} MONITOR ;


void monitor_trace(const char *label=nullptr, bool force_full=false, bool nl=true){
  static char buf[128] ;

  if (label != nullptr){
    sprintf(buf, "%8s", label) ;
  }
  else {
    sprintf(buf, "%8ld", INST_CNT) ;
  }
  Serial.print(buf) ;

  if ((STEP_CNT == 0)||(force_full)){
    sprintf(buf, " %2d PC:0x%04X  INST:0x%02X  EA:0x%04X ACC:%-3d X:%-3d Y:%-3d SP:0x%02X STATUS:0x%02X", 
      STEP_CNT, MONITOR.pc, MONITOR.inst, MONITOR.ea, MONITOR.acc, MONITOR.x, MONITOR.y, MONITOR.sp, MONITOR.status) ;
  }
  else {
    sprintf(buf, " %2d PC:0x%04X~ INST:0x%02X  ", STEP_CNT, MONITOR.pc, MONITOR.inst) ;
  }
  if (nl){
    strcat(buf, "\n") ;
  }
  Serial.print(buf) ;
}


void process_monitor(bool grab_inst){
    // See fetch()
    if ((grab_inst)&&(STEP_CNT == 3)){
      MONITOR.prev_inst = MONITOR.inst ;
      MONITOR.inst = DATA.read() ;
      CTRL.pulse(INST_S) ;
    }

    // See pc()
    if (MONITOR.inst == INST_PC){
      switch (STEP_CNT){
        case 2: MONITOR.prev_pc = MONITOR.pc ;
                MONITOR.pc = DATA.read() << 8 ; 
                break ;
        case 4: MONITOR.pc |= DATA.read() ; 
                break ;
      }
    }
    // See mon()
    else if (MONITOR.inst == INST_MON){
      switch (STEP_CNT){
        case  2: MONITOR.prev_pc = MONITOR.pc ;
                 MONITOR.pc = DATA.read() << 8 ; 
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


void process_inst(bool grab_inst=true, uint8_t max_step = 0xFF){
  bool prev_ctrl = false ; 
  while (STEP_CNT <= max_step){    
    process_monitor(grab_inst) ;
    
    if (STEP_CNT > 0){
      // This already happened for step 0 when we called STEP_CLR
      CTRL.pulse(CLK_ASYNC) ; 
      CTRL.pulse_sync() ;  
    }
     
    if (PINC & 0b100){ // A2, RAM_ctrl
      CTRL.process() ;
      prev_ctrl = true ;
    }
    else if (prev_ctrl){
      //ctrl_cache = 0 ;
      CTRL.clear_cache() ;
      DATA.reset() ;
    }
    
    if (DEBUG_MON){
      if ((MONITOR.inst != INST_MON)&&(MONITOR.inst != INST_PC)){
        if (DEBUG_STEP){
          monitor_trace(nullptr, false, false) ;
          if (DEBUG_STEP){
            Serial.print(F("  ")) ;
            Serial.print(STEP_CNT) ;
            Serial.print(" done...") ;
            while (! button_pressed(STEP)){} ;
            Serial.println() ;
          }
        }
        else {
          monitor_trace() ;
        }
      }
    }
               
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


void insert_inst(uint8_t opcode, bool process=true){
  DATA.write(opcode) ;
  MONITOR.inst = opcode ;
  CTRL.pulse(INST_S) ;
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
  CTRL.pulse(STEP_CLR) ;
  CTRL.pulse(PC_CLR) ;
  // Reset latches
  CTRL.pulse_sync() ;

  monitor_sample() ;
  monitor_trace("INIT  ->") ;
  
  // Initialize INST register to RST1
  insert_inst(INST_RST1) ;

  Serial.print(F("- Loading program to RAM...")) ;
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

  CTRL.pulse(STEP_CLR) ;
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
  while (1) {
    if (HALTED){
      pinMode(LED_BUILTIN, OUTPUT) ;
      digitalWrite(LED_BUILTIN, HIGH) ;
      Serial.print("Duration: ") ;
      Serial.print(millis() / 1000) ;
      Serial.println(" seconds.") ;
      while (1){} ;
    }

    process_inst() ;

    if ((PROGRESS)&&((INST_CNT % 10000) == 0)){
      monitor_sample(true) ; // PC-only monitor
      Serial.print(INST_CNT) ;
      Serial.print(" instructions executed (pc:0x") ;
      Serial.print(MONITOR.pc, HEX) ;
      Serial.print(", rate:") ;
      float rate = INST_CNT / (millis() / 1000.0) ;
      Serial.print(rate) ;
      Serial.println(" insts/sec)") ;
    }

    /*
    if ((MON_EVERY != 0)&&((INST_CNT % MON_EVERY) == 0)){
      monitor_sample() ; // Full monitor
      monitor_trace() ; 
    }
    else {
      monitor_sample() ; // PC-only monitor
    }
    
    // Let's check if the PC has changed 
    if (MONITOR.pc == MONITOR.prev_pc){
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
    */
    
    if (button_pressed(NMI)){
      process_interrupt(INST_NMI) ;
    }
    if (button_pressed(IRQ)){
      process_interrupt(INST_IRQ) ;
    }    
  }
}
