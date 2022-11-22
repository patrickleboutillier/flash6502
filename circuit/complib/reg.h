#ifndef REGISTER_H
#define REGISTER_H


#include "circuit.h"


template <uint32_t W> class reg : public component {
    public:
        input<W> data_in ;
        input<1> set, enable ;
        output<W> data_out ;
    //private:
        uint32_t _mem ;

    public:
        reg() : set(this), enable(this) {
            _mem = 0 ;
            data_out.drive(false) ;
        } ;

        void operator=(reg<W> r){
            _mem = r._mem ;
            always() ;
        }

        void operator=(uint32_t v){
            _mem = v & ((1 << W) - 1) ;
            always() ;
        }

        operator uint32_t(){
            return _mem ;
        }

        void always(){
            if (set){
                _mem = data_in ;
            }
            if (! enable){ // negative logic
                data_out.drive(true) ;
                data_out = _mem ;
            }
            else {
                data_out.drive(false) ;
            }
        } ;
} ;


#endif