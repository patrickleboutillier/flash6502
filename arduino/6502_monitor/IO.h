#ifndef IO_H
#define IO_H


#define LOADER_CMD    0x1B
#define LOADER_UPLOAD 0xFF
#define LOADER_STDIN  0x00
#define LOADER_STDOUT 0x01
#define LOADER_STDERR 0x02
#define LOADER_HALT   0x09

class IO {
  private:
    bool _loader ;
    
  public:
    IO(){
      _loader = false ;
    }

    void set_loader(){
      _loader = true ;  
    }
    
    // Not the real address here, just the lower 4 bits.
    uint8_t get_byte(uint8_t addr){
      switch (addr){
        case 0x0: {
          if (_loader){
            Serial.write(LOADER_CMD) ;
            Serial.write(LOADER_STDIN) ;
          }
          uint8_t data ;
          while (!Serial.available()) ;
          Serial.readBytes(&data, 1) ;
          return data ; // stdin
        }
      }
      
      return 0 ;
    }

    // Not the real address here, just the lower 4 bits.
    void set_byte(uint8_t addr, uint8_t data){
      switch (addr){
        case 0x0: // stdin
          return ;
        case 0x1: // stdout 
          if (_loader){
            Serial.write(LOADER_CMD) ;
            Serial.write(LOADER_STDOUT) ;
          }
          Serial.print((char)data) ;
          return ;
        case 0x2: // stderr 
          if (_loader){
            Serial.write(LOADER_CMD) ;
            Serial.write(LOADER_STDERR) ;
          }
          Serial.print((char)data) ;
          return ;
        case 0x9: // halt
          Serial.println("HALTED!") ;
          if (_loader){
            Serial.write(LOADER_CMD) ;
            Serial.write(LOADER_HALT) ;
          }
          HALTED = true ;
          return ;
      }
    }
} ;


#endif
