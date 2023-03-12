#ifndef CTRL_H
#define CTRL_H


//#define CTRL  A2         // Activate controller for vectors and IO
#define CTRL_ADDR0 A2
#define CTRL_ADDR1 A3
#define CTRL_ADDR2 A6
#define CTRL_ADDR3 A7

#define CLK_ASYNC  0b00100
#define STEP_CLR   0b01000
#define RAM_S      0b10000
#define INST_S     0b10100
#define PC_UP      0b11000
#define PC_CLR     0b11100

 
#define CTRL_pulse_async_fast()     asm("sbi 0x05, 2\ncbi 0x05, 2\n") ;
#define CTRL_pulse_step_clr_fast()  asm("sbi 0x05, 3\ncbi 0x05, 3\n") ;
#define CTRL_pulse_sync_fast()      asm("cbi 0x08, 1\nsbi 0x08, 1\n") ;


// Pins 12, 11, 10: PORTB, bits 4, 3, 2
// Sync is A1: PORTC, bit 2
// PC_e is A0: PORTC, bit 1
// CTRL_src is 13: PORTB, bit 5
class CTRL {
  private:
    DATA *_data ;
    VECTORS *_vectors ;
    IO *_io ;
    uint8_t _cache ; 
  
  public:
    CTRL(DATA *data, VECTORS *vectors, IO *io){
      _data = data ;
      _vectors = vectors ;
      _io = io ; 
      _cache = 0 ;
      // Set pins to output  
      DDRB  |= 0b00011100 ;
      DDRC  |= 0b00000011 ;
      PORTC |= 0b00000011 ;
    }

    inline void clear_cache(){
      _cache = 0 ;
    }
    
    inline void pulse_sync(){
      // Set control bits (bits 4, 3, 2), which are already 0.
      PORTC &= 0b11111101 ;
      PORTC |= 0b00000010 ;
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

    inline void PC_e_on(){
      PORTC &= 0b11111110 ;
    }

    inline void PC_e_off(){
      PORTC |= 0b00000001 ;
    }

    inline void CTRL_src_on(){
      PORTB |= 0b00100000 ;
    }

    inline void CTRL_src_off(){
      PORTB &= 0b11011111 ;
    }

    #define analogRead2Digital(apin)  (analogRead(apin) >= 512)
    inline void process(){
      if (! analogRead2Digital(CTRL_ADDR3)){  // RAM_e.read()
        CTRL_src_on() ;
        uint8_t addr = analogRead2Digital(CTRL_ADDR3) << 3 | analogRead2Digital(CTRL_ADDR2) << 2 | digitalRead(CTRL_ADDR1) << 1 | digitalRead(CTRL_ADDR0) ;  
        CTRL_src_off() ;
        // read from vectors or IO
        if (addr < 0xA){
          if (! _cache){
            _cache = _io->get_byte(addr) ;
          }
          _data->write(_cache) ;
        }
        else {
          _data->write(_vectors->get_byte(addr)) ;
        }
      }
      else {
        _cache = 0 ;
        _data->reset() ;     
      }
    
      if (! analogRead2Digital(CTRL_ADDR2)){  // RAM_s.read()
        // write to vectors or IO
        CTRL_src_on() ;
        uint8_t addr = analogRead2Digital(CTRL_ADDR3) << 3 | analogRead2Digital(CTRL_ADDR2) << 2 | digitalRead(CTRL_ADDR1) << 1 | digitalRead(CTRL_ADDR0) ;  
        CTRL_src_off() ;
        if (addr < 0xA){
          _io->set_byte(addr, _data->read()) ;
        }
        else {
          _vectors->set_byte(addr, _data->read()) ;
        }
      }
    }
} ;


#endif
