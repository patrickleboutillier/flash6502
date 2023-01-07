#ifndef REGCLK_H
#define REGCLK_H


#include "circuit.h"


template <uint32_t W> class regclk : public component {
    public:
        input<W> data_in ;
        input<1> clk, enable ;
        output<W> data_out ;
    private:
        uint32_t _mem ;
        uint8_t _prev_clk ;
    public:
        regclk() : data_in(this), clk(this), enable(this) {
            _mem = rand() ; // Initialize with random value
            data_out.drive(false) ;
            _prev_clk = 1 ;
        } ;

        operator uint32_t(){
            return _mem ;
        }

        void always(const void *trigger){
            if ((clk)&&(! _prev_clk)){
                _mem = data_in ;
            }
            _prev_clk = clk ;
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