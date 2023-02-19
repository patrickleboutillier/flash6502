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

class CTRL_OUT {
  private:
    CTRLSIG *clk_sync ;
    
  public:
    CTRL_OUT(CTRLSIG *_clk_sync){
      clk_sync = _clk_sync ;
      // Set pins to output  
      DDRB |= 0b00011100 ;
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
      clk_sync->pulse() ;
      // Clear control bits
      PORTB &= 0b11100011 ;
      clk_sync->pulse() ;
    }

    inline void on(uint8_t cmd){
      PORTB |= cmd ;
    }

    inline void off(uint8_t cmd){
      PORTB &= 0b11100011 ;
    }
} ;


#endif
