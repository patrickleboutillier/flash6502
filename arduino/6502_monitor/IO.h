#ifndef IO_H
#define IO_H


class IO {
  public:
    IO(){
    }

    // Not the real address here, just the lower 4 bits.
    uint8_t get_byte(uint8_t addr){
        switch (addr){
            case 0x0:
              return 0 ; // stdin
            case 0x1: 
              return 0 ; // stdout
        }
        
        return 0 ;
    }

    // Not the real address here, just the lower 4 bits.
    void set_byte(uint8_t addr, uint8_t data){
        switch (addr){
            case 0x0: // stdin
              return ;
            case 0x1: // stdout 
              Serial.print((char)data) ;
              return ;
        }
    }
} ;


#endif
