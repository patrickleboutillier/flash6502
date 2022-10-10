#ifndef BUF_H
#define BUF_H


#include "wire.h"
#include "sensor.h"


class buf : public sensor {
    public:
        wire *_in ;
        wire *_out ;

    public:
        buf(wire &in, wire &out) {
            _in = &in ;
            _out = &out ;
            add_signal(_in) ;
        }


        buf(wire *in, wire *out) {
            _in = in ;
            _out = out ;
            add_signal(_in) ;
        }


        void always() {
            _out->v(_in->v()) ;
        }
} ;


#endif