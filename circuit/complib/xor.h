#ifndef XOR_H
#define XOR_H


#include "circuit.h"


template <uint32_t W> class xor_ : public component {
    public:
        input<W> a, b ;
        output<W> c ;
    public:
        xor_() : a(this), b(this) {
        } ;

        void always(){
            c.set_value(a.get_value() ^ b.get_value()) ;
        } ;
} ;


#endif