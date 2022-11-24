#ifndef CONTROL_1_ROM_H
#define CONTROL_1_ROM_H


#include "circuit.h"
#include "../microcode.h"


class CONTROL_1_ROM : public component {
    public:
        input<8> inst ;
        input<1> n, v, z, c ;
        input<4> step ;
        input<2> phase ;
        output<1> X_s, X_e, Y_s, Y_e, ACC_s, ACC_e ;

    public:
        CONTROL_1_ROM() : inst(this), n(this), v(this), z(this), c(this), step(this), phase(this) {
        } ;

        uint8_t make_cw(){
            return 
                X_s << 0 |
                X_e << 1 |
                Y_s << 2 |
                Y_e << 3 |
                ACC_s << 4 |
                ACC_e << 5 ;
        }

        void always(){
            uint8_t prev = make_cw() ;
            uint8_t cw = (microcode[inst << 10 | n << 9 | v << 8 | z << 7 | c << 6 | step << 2 | phase] >> 0) & 0xFF ;

            #define set_signal_1(output, bit) if (((cw >> bit) & 0x1) != ((prev >> bit) & 0x1)){ output = cw >> bit ; }

            set_signal_1(X_s, 0) ;
            set_signal_1(X_e, 1) ;
            set_signal_1(Y_s, 2) ;
            set_signal_1(Y_e, 3) ;
            set_signal_1(ACC_s, 4) ;
            set_signal_1(ACC_e, 5) ;

        } ;
} ;


#endif