#ifndef RAM_H
#define RAM_H


#include "circuit.h"


class RAM : public component {
    public:
        input<8> data_in, addrh, addrl ;
        input<1> set, enable ;
        output<8> data_out ;
    private:
        uint8_t _mem[256][256] ;

    public:
        RAM() : set(this), enable(this) {
            data_out.drive(false) ;
        } ;

        void always(){
            if (set){
                _mem[addrh][addrl] = data_in ;
            }
            if (enable){
                data_out.drive(true) ;
                data_out = _mem[addrh][addrl] ;
            }
            else {
                data_out.drive(false) ;
            }
        } ;
} ;


#endif