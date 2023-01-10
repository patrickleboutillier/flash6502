#ifndef CTRL_IN_H
#define CTRL_IN_H


#include "circuit.h"


// Simulates a SN74HC157
class CTRL_IN : public component {
    public:
        input<1> ctrl1, ctrl2, ctrl3, ctrl4 ;
        input<8> addrl ;
        input<1> ctrl_or_addr ;
        output<1> out1, out2, out3, out4 ;
    private:
        output<1> *_src ;

    public:
        CTRL_IN(output<1> *src) : ctrl1(this), ctrl2(this), ctrl3(this), ctrl4(this), addrl(this), ctrl_or_addr(this) {
            _src = src ;
            _src->connect(ctrl_or_addr) ;
        } ;


        void always(const void *trigger){
            bool ctrl = !ctrl_or_addr ;
            out1 = (ctrl ? ctrl1 : (addrl >> 0)) ;
            out2 = (ctrl ? ctrl2 : (addrl >> 1)) ;
            out3 = (ctrl ? ctrl3 : (addrl >> 2)) ;
            out4 = (ctrl ? ctrl4 : (addrl >> 3)) ;
        } ;


        uint8_t get_addr(){
            (*_src) = 1 ;
            uint8_t ret = out4 << 3 | out3 << 2 | out2 << 1 | out1 << 0 ;
            (*_src) = 0 ; 
            return ret ;
        }
} ;


#endif