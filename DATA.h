#ifndef DATA_H
#define DATA_H


#include "hdl/wire.h"
#include "hdl/bus.h"
#include "hdl/sensor.h"


class DATA : public sensor {
    public:
        bus data ;
        wire Z ;
        wire N ;
        
    public:
        DATA() : data(8, 0) {
            add_signal(&data) ;
        }


        void always() {
            uint8_t v = data.v() ;
            Z.v(v == 0) ;
            N.v(v & 0b10000000) ;
        }
} ;


#endif