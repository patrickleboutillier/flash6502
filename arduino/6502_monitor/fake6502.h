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
} MONITOR, MONITOR_PREV ;


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
      MONITOR_PREV = MONITOR ;
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


void process_inst(bool grab_inst=true, uint8_t max_step = 0xFF){
  bool prev_ctrl = false ; 
  while (STEP_CNT <= max_step){    
    process_monitor(grab_inst) ;
    
    if (STEP_CNT > 0){
      // This already happened for step 0 when we called STEP_CLR
      CTRL_OUT.pulse(CLK_ASYNC) ;    
      CTRL_OUT.pulse_sync() ;  
    }
     
    if (PINC & 0b100){ // A2, RAM_ctrl
      process_ctrl() ;
      prev_ctrl = true ;
    }
    else if (prev_ctrl){
      ctrl_cache = 0 ;
      DATA.reset() ;
    }

    if ((MON_EVERY == 1)&&(MONITOR.inst == 0xEA)&&(MONITOR_PREV.inst == 0x10)){
      monitor_trace(nullptr, false) ;
      pause() ;
    }
    if ((MONITOR.inst != INST_MON)&&(MONITOR.inst != INST_PC)){
      if ((DEBUG_MON)||(DEBUG_STEP)){
        monitor_trace(nullptr, false) ;
        if (DEBUG_STEP){
          Serial.print(F("  ")) ;
          Serial.print(STEP_CNT) ;
          Serial.print(" done...") ;
          while (! button_pressed(STEP)){} ;
        }
        Serial.println() ;
      }
    }
               
    if (PINC & 0b1000){ // A3, INST_done
      if ((MONITOR.inst != INST_MON)&&(MONITOR.inst != INST_PC)){
        INST_CNT++ ;
      }
      // Reset step counter.
      CTRL_OUT.pulse(STEP_CLR) ;
      CTRL_OUT.pulse_sync() ; 
      STEP_CNT = 0 ;
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
  CTRL_OUT.pulse_sync() ;

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
    CTRL_PC_e.toggle() ;
    CTRL_OUT.pulse_with_sync(RAM_S) ;
    CTRL_PC_e.toggle() ;
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
      pinMode(LED_BUILTIN, OUTPUT) ;
      digitalWrite(LED_BUILTIN, HIGH) ;
      while (1){} ;
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

    if (INST_CNT == 29000){
      MON_EVERY = 1 ;
    }
    if (INST_CNT == 31000){
      MON_EVERY = 1000 ;
    }
      
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
