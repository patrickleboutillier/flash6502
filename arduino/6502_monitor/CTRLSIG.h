#ifndef CTRLSIG_H
#define CTRLSIG_H

#include "Extension.h"
#include "Arduino.h"


class CTRLSIG {
  private:
    Extension *_e ;
    uint8_t _pin ;
    uint8_t _mode ;
    uint8_t _cache ;
    bool _setup ;
    static int _nb ;
    static int _nb_setup ;

  public:
    CTRLSIG(Extension *e, uint8_t pin, bool neglog = false) {
      _e = e ;
      _pin = pin ;
      _cache = neglog ? HIGH : LOW ;
      _setup = false ;
      _nb++ ;
    }

    void setup(){
      _setup = true ;
      if (_e != NULL){
        _e->pinMode(_pin, OUTPUT) ;
      }
      else {
        pinMode(_pin, OUTPUT) ;
      }
      write(_cache) ;
      _nb_setup++ ;
    }

    void operator=(uint8_t v){
      write(v) ;
    }
        
    void write(uint8_t v){
      _cache = v ;
      if (_e != NULL){
        _e->digitalWriteFast(_pin, v) ;
        delayMicroseconds(25) ;
      }
      else {
        digitalWrite(_pin, v) ;
      }
    }

    uint8_t read(){
      return _cache ;  
    }
    
    void toggle(){
      write(! _cache) ;
    }

    void pulse(){
      toggle() ;
      toggle() ;
    }

    static int count(){
      return _nb ;
    }

    static void check(){
      if (_nb_setup != _nb){
        Serial.println("WARNING: Control signal setup mismatch!!!") ;
      }
    }
} ;


int CTRLSIG::_nb = 0 ; 
int CTRLSIG::_nb_setup = 0 ; 


#endif
