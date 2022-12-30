#ifndef MUX2_H
#define MUX2_H


#include "circuit.h"


template <uint32_t W> class mux2 : public component {
    public:
        input<W> a, b ;
        input<1> sel ;
        output<W> c ;
    public:
        mux2() : a(this), b(this), sel(this) {
        } ;

        void always(const void *trigger){
            c = (sel == 0 ? a : b) ;
        } ;
} ;


#endif