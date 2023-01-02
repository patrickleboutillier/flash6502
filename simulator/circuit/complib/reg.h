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
        reg() : data_in(this), set(this), enable(this) {
            _mem = rand() ; // Initialize with random value
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

        void always(const void *trigger){
            if (set){
                _mem = data_in ;
            }
            else if (trigger == &data_in){
                // Ignore changes on the data bus if set is not active.
                return ;    
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