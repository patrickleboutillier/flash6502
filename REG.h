#ifndef REG_H
#define REG_H

#include "hdl/bus.h"
#include "hdl/buf.h"
#include "hdl/sensor.h" 


class REG : public sensor {
    public:
        wire set ;
        wire enable ;
    private:
        bus *_in ;
        bus *_out ;
        uint8_t _reg ;

    public:
        REG(bus *in, bus *out) {
            _in = in ;
            _out = out ;
            add_signal(in) ;
            add_signal(out) ;
            add_signal(&set) ;
            add_signal(&enable) ;
            _reg = 0 ;
        }


        void always() {
            if (set.v()){
                _reg = _in->v() ;
            }
            if (enable.v()){
                _out.v(_reg) ;
            }
        }


        void set(){
            set.v(1) ;
            set.v(0) ;
        }


        void enable(){
            enable.v(1) ;
        }


        void disable(){
            enable.v(0) ;
        }
} ;


#endif