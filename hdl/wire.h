#ifndef WIRE_H
#define WIRE_H


#include "bus.h"


class wire : public signal {
    private:
        bus *_bus ;
        uint8_t _bit ;

    public:
        wire(bool v = 0){
            _bus = new bus(1, 0) ;
            _bit = 0 ;
            this->v(v) ;
        }


        wire(bus *bus, uint8_t bit, bool v = 0){
            _bus = bus ;
            _bit = bit ;
            this->v(v) ;
        }


        inline bool v(){
            return (_bus->v() >> _bit) & 1 ;
        }


        void v(bool v){
            uint32_t bv = (_bus->v() & ~(1 << _bit)) | v << _bit ;
            _bus->v(bv) ;
        }


        void connect(sensor *s){
            _bus->connect(s, 1 << _bit) ;
        }
} ;


wire *new_wire(bus *bus, uint8_t bit){
    return new wire(bus, bit) ;
}


#endif
