#ifndef BUS_H
#define BUS_H


#include "circuit.h"


template <uint32_t W> class bus : public component {
    public:
        input<W> data_in ;
        output<W> data_out ;

    public:
        bus() : data_in(this) {
        } ;

        void always(const void *trigger){
            data_out = data_in ;
        } ;
} ;


#endif