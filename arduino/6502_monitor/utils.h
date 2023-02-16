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


inline uint8_t analogRead2Digital(int apin){
  bool dv = (analogRead(apin) >= 512) ;
  return dv ;
}


void pause(){
   Serial.println(F("\nPAUSE:")) ;
   while (! button_pressed(STEP)){} ; 
}


/*
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


void set_ea(uint16_t ea){
  DATA.write(ea >> 8) ;
  EAh_s.pulse() ;
  DATA.reset() ;
  DATA.write(ea & 0xFF) ;
  EAl_s.pulse() ;
  DATA.reset() ;
}


uint8_t get_ram_ea(){
  EAl_e.toggle() ; 
  EAh_e.toggle() ;
  RAM_e.toggle() ;
  uint8_t data = DATA.read() ;
  RAM_e.toggle() ;
  EAl_e.toggle() ; 
  EAh_e.toggle() ;
  return data ;  
}


uint8_t peek_ram(uint16_t addr){
  set_ea(addr) ;
  uint8_t data = get_ram_ea() ;
  return data ;
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
*/

/* uint8_t get_status(){
  ST_e.toggle() ;
  uint8_t status = DATA.read() ;
  ST_e.toggle() ;
  return status ;
} */


/* uint8_t set_status(uint8_t s){
  DATA.write(s) ;
  ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ;
  ST_s.pulse() ;
  ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ;
  DATA.reset() ;
} */
