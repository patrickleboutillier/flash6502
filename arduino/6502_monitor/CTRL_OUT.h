#ifndef CTRL_OUT_H
#define CTRL_OUT_H


#define CLK_ASYNC  0b00100
//#define CLK_SYNC   0b01000
#define STEP_CLR   0b01100
#define RAM_S      0b10000
#define INST_S     0b10100
#define PC_UP      0b11000
#define PC_CLR     0b11100


// Pins 12, 11, 10: PORTB, bits 4, 3, 2
// Sync is A1: PORTC, bit 2
class CTRL_OUT {
  public:
    CTRL_OUT(){
      // Set pins to output  
      DDRB |= 0b00011100 ;
      DDRC |= 0b00000010 ;
    }
    
    inline void pulse_sync(){
      // Set control bits (bits 4, 3, 2), which are already 0.
      PORTC |= 0b00000010 ;
      PORTC &= 0b11111101 ;
    }
    
    inline void pulse(uint8_t cmd){
      // Set control bits (bits 4, 3, 2), which are already 0.
      PORTB |= cmd ;
      // Clear control bits
      PORTB &= 0b11100011 ;            
    }

    inline void pulse_with_sync(uint8_t cmd){
      // Set control bits (bits 4, 3, 2), which are already 0.
      PORTB |= cmd ;
      pulse_sync() ;
      // Clear control bits
      PORTB &= 0b11100011 ;
      pulse_sync() ;
    }
} ;


#endif
