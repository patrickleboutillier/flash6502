#ifndef DATA_h
#define DATA_h


// Pins 9, 8, 7, 6, 5, 4, 3, 2 -> PORTB:bits 2,3,4,5,6,7, PORTD:bits 0, 1

class DATA {
  private:
    bool _enabled ;
    byte _cache ;
    
  public:
    DATA(){
       _enabled = false ;
      _cache = 0 ;
      DDRB &= ~0b00000011 ;
      DDRD &= ~0b11111100 ; 
    }

    inline void reset(){
      if (_enabled){
        DDRB &= ~0b00000011 ;
        DDRD &= ~0b11111100 ;
        _enabled = false ;  
      }
    }
    
    inline byte read(){
      if (_enabled){
        // One part wants to read from the DATA, while another one is writing.
        // We give the reader the out cached value.
        return _cache ;
      }
      
      return (PINB & 0b00000011) << 6 | (PIND & 0b11111100) >> 2 ;
    }
    
    inline void write(byte b){
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
