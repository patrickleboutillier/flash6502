#ifndef CTRL_OUT_H
#define CTRL_OUT_H


#define CLK_ASYNC  0b00100
//#define CLK_SYNC   0b01000
#define INST_S     0b01000
#define STEP_CLR   0b01100
#define RAM_S      0b10000
//#define INST_S     0b10100
#define PC_UP      0b11000
#define PC_CLR     0b11100

#define delay()    //delayMicroseconds(5) ;


// Pins 12, 11, 10: PORTB, bits 4, 3, 2
// Sync is A1: PORTC, bit 2
// PC_e is A0: PORTC, bit 1
class CTRL_OUT {
  public:
    CTRL_OUT(){
      // Set pins to output  
      DDRB  |= 0b00011100 ;
      DDRC  |= 0b00000011 ;
      PORTC |= 0b00000011 ;
    }
    
    inline void pulse_sync(){
      // Set control bits (bits 4, 3, 2), which are already 0.
      PORTC &= 0b11111101 ;
      delay() ;
      PORTC |= 0b00000010 ;
      delay() ;
    }
    
    inline void pulse(uint8_t cmd){
      // Set control bits (bits 4, 3, 2), which are already 0.
      PORTB |= cmd ;
      delay() ;
      // Clear control bits
      PORTB &= 0b11100011 ;            
      delay() ;
    }

    inline void pulse_with_sync(uint8_t cmd){
      // Set control bits (bits 4, 3, 2), which are already 0.
      PORTB |= cmd ;
      delay() ;
      pulse_sync() ;
      // Clear control bits
      PORTB &= 0b11100011 ;
      delay() ;
      pulse_sync() ;
    }

    void PC_e_on(){
      PORTC &= 0b11111110 ;
      delay() ;
    }

    void PC_e_off(){
      PORTC |= 0b00000001 ;
      delay() ;
    }
} ;


#endif
