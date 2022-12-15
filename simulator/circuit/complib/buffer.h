#ifndef BUFFER_H
#define BUFFER_H


#include "circuit.h"


template <uint32_t W> class buffer : public component {
    public:
        input<W> a ;
        output<W> b ;
    public:
        buffer() : a(this) {
        } ;

        void always(){
            b.set_value(a) ;
        } ;
} ;


#endif