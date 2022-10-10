#ifndef BUS_H
#define BUS_H


#include <stdlib.h>
#include <stdint.h>
#include "sensor.h"


class wire ;
class bus ;
wire *new_wire(bus *bus, uint8_t bit) ;


class bus : public signal {
    private:
        size_t _n ;
        uint32_t _v ;
        wire **_wires ;

    public:
        bus(size_t n, uint32_t v = 0){
            _n = n ;
            _v = v ;
            _wires = (wire **)calloc(n, sizeof(wire *)) ;
        }


        inline uint32_t v(){
            return _v ;
        }


        void v(uint32_t v){
            if (v != _v){
                uint32_t changed = v ^ _v ;
                _v = v ;
                for (int i = 0 ; i < _sensors.size() ; i++){
                    sensor *s = _sensors[i].first ;
                    uint32_t filter = _sensors[i].second ;
                    if ((filter == 0)||(filter & changed)){
                        s->always() ;
                    }
                }
            }
        }


        wire *bit(uint8_t bit){
            if (_wires[bit] == NULL){
                _wires[bit] = new_wire(this, bit) ;
            }

            return _wires[bit] ;
        }

} ;


#endif
