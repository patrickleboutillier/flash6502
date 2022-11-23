#ifndef TRISTATE_H
#define TRISTATE_H


#include "circuit.h"


template <uint32_t W> class tristate : public component {
    public:
        input<W> data_in ;
        input<1> enable ;
        output<W> data_out ;

    public:
        tristate() : data_in(this), enable(this) {
            data_out.drive(false) ;
        } ;

        void always(){
            if (! enable){ // negative logic
                data_out.drive(true) ;
                data_out = data_in ;
            }
            else {
                data_out.drive(false) ;
            }
        } ;
} ;


#endif