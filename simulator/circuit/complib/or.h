#ifndef OR_H
#define OR_H


#include "circuit.h"


template <uint32_t W> class or_ : public component {
    public:
        input<W> a, b ;
        output<W> c ;
    public:
        or_() : a(this), b(this) {
        } ;

        void always(){
            c.set_value(a.get_value() | b.get_value()) ;
        } ;
} ;


#endif