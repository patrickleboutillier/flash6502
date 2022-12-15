#ifndef STATUS_H
#define STATUS_H

#include "Extension.h"


class STATUS {
  private:
    Extension *_e ;
    byte _pin_N, _pin_V, _pin_Z, _pin_C ;
        
  public: // To match simulator interface
    byte N, V, Z, C ;
    
  public:
    STATUS(Extension *e, byte pin_N, byte pin_V, byte pin_Z, byte pin_C){
      _e = e ;
      _pin_N = pin_N ;
      _pin_V = pin_V ;
      _pin_Z = pin_Z ;
      _pin_C = pin_C ;
    }

    void setup(){
      _e->pinMode(_pin_N, INPUT) ;
      _e->pinMode(_pin_V, INPUT) ;
      _e->pinMode(_pin_Z, INPUT) ;
      _e->pinMode(_pin_C, INPUT) ;
    }
    
    void latch(){
      N = _e->digitalRead(_pin_N) ;
      V = _e->digitalRead(_pin_V) ;
      Z = _e->digitalRead(_pin_Z) ;
      C = _e->digitalRead(_pin_C) ;
    }
} ;


#endif
