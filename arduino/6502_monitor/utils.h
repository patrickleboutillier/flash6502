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


/*inline uint8_t analogRead2Digital(int apin){
  bool dv = (analogRead(apin) >= 512) ;
  return dv ;
}*/


void pause(){
   Serial.println(F("\nPAUSE:")) ;
   while (! button_pressed(STEP)){} ; 
}
