#ifndef AND_H
#define AND_H


#include "circuit.h"


template <uint32_t W> class and_ : public component {
    public:
        input<W> a, b ;
        output<W> c ;
    public:
        and_() : a(this), b(this) {
        } ;

        void always(const void *trigger){
            c.set_value(a.get_value() & b.get_value()) ;
        } ;
} ;


#endif