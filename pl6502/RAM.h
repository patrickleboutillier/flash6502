#ifndef RAM_H
#define RAM_H


#include "circuit.h"


class RAM : public component {
    public:
        input<16> address ;
        input<8> data_in ;
        input<1> set, enable ;
        output<8> data_out ;
    private:
        uint8_t _mem[0x10000] ;

    public:
        RAM() : set(this), enable(this) {
            data_out.drive(false) ;
        } ;

        void always(){
            if (set){
                _mem[address] = data_in ;
            }
            if (enable){
                data_out.drive(true) ;
                data_out = _mem[address] ;
            }
            else {
                data_out.drive(false) ;
            }
        } ;
} ;


#endif