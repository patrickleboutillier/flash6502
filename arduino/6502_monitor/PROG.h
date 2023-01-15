#ifndef PROG_H
#define PROG_H

#include "Extension.h"

// A program definition in a stream of bytes

class PROG {
  private:
    Extension *_e ;
    bool _progmem ;
    bool _serial ;
    const char *_name ;
    const uint8_t *_bytes ;
    uint32_t _len ;
    uint32_t _pc ;
    uint16_t _start_addr ;
    uint16_t _int_addr ;
    uint16_t _nmi_addr ;
    uint16_t _done_addr ;
    
  public:
    // Program that is defined in the Arduino RAM or flash
    PROG(const char *name, const uint8_t *bytes, uint16_t len, bool progmem = false, uint16_t start_addr = 0, uint16_t int_addr = 0, uint16_t nmi_addr = 0, uint16_t done_addr = 0){
        _pc = 0 ;
        _name = name ;
        _bytes = bytes ;
        _len = len ;
        _start_addr = start_addr ;
        _int_addr = int_addr ;
        _nmi_addr = nmi_addr ;
        _done_addr = done_addr ;
        _progmem = progmem ;
        _serial  = false ;
        _e = NULL ;
    }

    // Program that is defined in an Arduino Entension
    PROG(const char *name, Extension *e, uint16_t len, uint16_t start_addr = 0, uint16_t int_addr = 0, uint16_t nmi_addr = 0, uint16_t done_addr = 0){
        _pc = 0 ;
        _name = name ;
        _bytes = NULL ;
        _len = len ;
        _start_addr = start_addr ;
        _int_addr = int_addr ;
        _nmi_addr = nmi_addr ;
        _done_addr = done_addr ;
        _progmem = false ;
        _serial  = false ;
        _e = e ;
    }

    // Program that is defined though the serial port
    PROG(const char *name){
        _pc = 0 ;
        _name = name ;
        _bytes = NULL ;
        _len = 0x10000 ;
        _start_addr = 0 ;
        _int_addr = 0 ;
        _nmi_addr = 0 ;
        _done_addr = 0 ;
        _progmem = false ;
        _serial  = true ;
        _e = NULL ;
    }
    
    const char *name(){
        return _name ;
    }

    uint32_t len(){
        return _len ;
    }

    int get_next_byte(){
        if (_pc >= _len){
            return -1 ;
        }

        uint8_t data = 0 ;
        if (_e != NULL){
            data = _e->pgm_read_byte_(_pc) ;
        }
        else if (_serial){
            if (_pc == 0){
                Serial.write(LOADER_CMD) ;
                Serial.write(LOADER_UPLOAD) ;
            }
            Serial.readBytes(&data, 1) ;
        } 
        else if (_progmem){
            data = pgm_read_byte(_bytes + _pc) ;
        } 
        else {
            data = ((byte *)_bytes)[_pc] ;
        }
        
        switch (_pc){
            case 0xFFFA: _nmi_addr = data ; break ;
            case 0XFFFB: _nmi_addr |= data << 8 ; break ;
            case 0xFFFC: _start_addr = data ; break ;
            case 0XFFFD: _start_addr |= data << 8 ; break ;
            case 0xFFFE: _int_addr = data ; break ;
            case 0XFFFF: _int_addr |= data << 8 ; break ;
        }
        
        _pc++ ;
        
        return data ;
    }

    uint16_t start_addr(){
        return _start_addr ;
    }

    uint16_t int_addr(){
        return _int_addr ;
    }

    uint16_t nmi_addr(){
        return _nmi_addr ;
    }

    uint16_t done_addr(){
        return _done_addr ;
    }

    bool is_done(uint16_t pc){
        return (_done_addr != 0 ? pc == _done_addr : false) ;
    }

    void describe(){
        Serial.print(F("\nProgram to run is '")) ; Serial.print(_name) ; Serial.println(F("':")) ;
        Serial.print(F("- It has ")) ; Serial.print(_len) ; Serial.println(F(" instructions")) ;
        Serial.print(F("- Reset vector is 0x")) ; Serial.println(_start_addr, HEX) ;
        Serial.print(F("- Interrupt vector is 0x")) ; Serial.println(_int_addr, HEX) ;
        Serial.print(F("- Non-maskable interrupt vector is 0x")) ; Serial.println(_nmi_addr, HEX) ;
        if (_done_addr){
            Serial.print(F("- It will be considered done when PC reaches 0x")) ;
            Serial.println(_done_addr, HEX) ;
        }
    }
} ;


#endif
