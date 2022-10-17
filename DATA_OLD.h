#ifndef DATA_OLD_H
#define DATA_OLD_H


#include "hdl/wire.h"
#include "hdl/bus.h"
#include "hdl/sensor.h"


class DATA_OLD : public sensor {
    public:
        bus data ;
        wire Z ;
        wire N ;
        
    public:
        DATA_OLD() : data(8, 0) {
            add_signal(&data) ;
        }


        void always() {
            uint8_t v = data.v() ;
            Z.v(v == 0) ;
            N.v(v & 0b10000000) ;
        }
} ;


#endif