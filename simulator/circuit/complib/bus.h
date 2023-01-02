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
            // Simulate pull down resistor if data_in is not driven
            data_out = (data_in.driven() ? data_in.get_value() : 0) ;
        } ;
} ;


#endif