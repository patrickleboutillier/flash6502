#ifndef BUS_h
#define BUS_h

#include "Arduino.h"

// Pins 9, 8, 7, 6, 5, 4, 3, 2 -> PORTB:bits 2,3,4,5,6,7, PORTD:bits 0, 1

class BUS {
  private:
    bool _enabled ;
    byte _cache ;
    
  public:
    BUS(){
       _enabled = false ;
      _cache = 0 ;
    }
    
    void setup(){
        DDRB &= ~0b00000011 ;
        DDRD &= ~0b11111100 ;    
    }
    
    void reset(){
      if (_enabled){
        DDRB &= ~0b00000011 ;
        DDRD &= ~0b11111100 ;
        _enabled = false ;  
      }
    }
    
    byte read(){
      if (_enabled){
        // One part wants to read from the BUS, while another one is writing.
        // We give the reader the out cached value.
        return _cache ;
      }
      
      return (PINB & 0b00000011) << 6 | (PIND & 0b11111100) >> 2 ;
    }
    
    void write(byte b){
      if (! _enabled){
        DDRB |= 0b00000011 ;
        DDRD |= 0b11111100 ;
        _enabled = true ;
      }

      PORTB = (PORTB & ~0b00000011) | b >> 6 ;
      PORTD = (PORTD & ~0b11111100) | b << 2 ;
    
      _cache = b ;      
    }

} ;

#endif
