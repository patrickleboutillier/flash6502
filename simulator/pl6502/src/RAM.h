#ifndef RAM_H
#define RAM_H


#include "circuit.h"


class RAM : public component {
    public:
        input<8> data_in, addrh, addrl ;
        input<1> set, enable ;
        output<8> data_out, ctrl ;
    private:
        uint8_t _mem[256][256] ;

    public:
        RAM() : data_in(this), addrh(this), addrl(this), set(this), enable(this) {
            data_out.drive(false) ;

            // Fill RAM with garbage
            for (int i = 0 ; i < 256 ; i++){
                for (int j = 0 ; j < 256 ; j++){
                    _mem[i][j] = rand() & 0xFF ;
                }
            }
        } ;

        void always(){
            // RAM is limited to the range 0x0000 => 0xF7FF
            // The rest of the address space is assigned to the controller.
            // This means the the controller handles the vectors in the range 0xFFFA => 0xFFFF
            if ((addrh & 0xF8) == 0xF8){
                ctrl = 1 ;
                return ;
            }
            else {
                ctrl = 0 ;
            }

            if (! set){
                _mem[addrh][addrl] = data_in ;
            }
            if (! enable){ // negative logic
                data_out.drive(true) ;
                data_out = _mem[addrh][addrl] ;
            }
            else {
                data_out.drive(false) ;
            }
        } ;
} ;


#endif