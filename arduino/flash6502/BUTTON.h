#ifndef BUTTON_H
#define BUTTON_H

#define DEBOUNCE_DELAY_MS 50


class BUTTON {
  private:
    bool _state, _last_state ;
    uint8_t _pin ;
    unsigned long _last_debounce_time ;

  public:  
    BUTTON(uint8_t pin){
      _pin = pin ;
      _state = LOW ;
      _last_state = _state ;
      _last_debounce_time = 0 ;
    }
  
    bool pressed(){      
      bool ret = 0 ;
      bool reading = digitalRead(_pin) ;
      if (reading != _last_state) {
        _last_debounce_time = millis() ;
      }
      
      if ((millis() - _last_debounce_time) > DEBOUNCE_DELAY_MS){
        if (reading != _state){
          _state = reading ;
          if (_state == LOW){
            ret = 1 ;
          }
        }
      }
    
      // save the reading. Next time through the loop, it'll be the lastButtonState:
      _last_state = reading ;
       
      return ret ;
    }
} ;

#endif
