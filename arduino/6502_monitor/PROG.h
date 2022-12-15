#ifndef PROG_H
#define PROG_H

#include "Extension.h"


class PROG {
  private:
    Extension *_e ;
    bool _progmem ;
    const char *_name ;
    const uint8_t *_bytes ;
    uint32_t _len ;
    uint16_t _start_addr ;
    uint16_t _int_addr ;
    uint16_t _nmi_addr ;
    uint16_t _done_addr ;
    
  public:
    // Program that is defined in the Arduino or simulator RAM
    PROG(const char *name, const uint8_t *bytes, uint16_t len, uint16_t start_addr = 0, uint16_t int_addr = 0, uint16_t nmi_addr = 0, uint16_t done_addr = 0){
        _name = name ;
        _bytes = bytes ;
        _len = len ;
        _start_addr = start_addr ;
        _int_addr = int_addr ;
        _nmi_addr = nmi_addr ;
        _done_addr = done_addr ;
        _progmem = false ;
        _e = NULL ;
    }

    // Program that is defined in the Arduino flash
    PROG(const char *name, const void *bytes, uint16_t len, uint16_t start_addr = 0, uint16_t int_addr = 0, uint16_t nmi_addr = 0, uint16_t done_addr = 0){
        _name = name ;
        _bytes = (byte *)bytes ;
        _len = len ;
        _start_addr = start_addr ;
        _int_addr = int_addr ;
        _nmi_addr = nmi_addr ;
        _done_addr = done_addr ;
        _progmem = true ;
        _e = NULL ;
    }

    // Program that is defined in an Arduino Entension
    PROG(const char *name, Extension *e, uint16_t len, uint16_t start_addr = 0, uint16_t int_addr = 0, uint16_t nmi_addr = 0, uint16_t done_addr = 0){
        _name = name ;
        _bytes = NULL ;
        _len = len ;
        _start_addr = start_addr ;
        _int_addr = int_addr ;
        _nmi_addr = nmi_addr ;
        _done_addr = done_addr ;
        _progmem = false ;
        _e = e ;
    }

    const char *name(){
        return _name ;
    }

    uint32_t len(){
        return _len ;
    }

    uint8_t get_byte(uint16_t addr){
        if (addr < _len){
            if (_e != NULL){
                return _e->pgm_read_byte_(addr) ;
            }
            else if (_progmem){
                return pgm_read_byte(_bytes + addr) ;
            } 
            else {
                return ((byte *)_bytes)[addr] ;
            }
        }
        
        return 0 ;
    }

    uint16_t start_addr(){
        return _start_addr ;
    }

    uint16_t int_addr(){
        return _int_addr ;
    }

    uint16_t nmi_addr(){
        return _int_addr ;
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
