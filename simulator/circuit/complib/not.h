#ifndef NOT_H
#define NOT_H


#include "circuit.h"


template <uint32_t W> class not_ : public component {
    public:
        input<W> a ;
        output<W> b ;
    public:
        not_() : a(this) {
        } ;

        void always(){
            b.set_value(~a.get_value()) ;
        } ;
} ;


#endif