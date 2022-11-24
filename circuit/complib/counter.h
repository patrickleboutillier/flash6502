#ifndef COUNTER_H
#define COUNTER_H


#include "circuit.h"

// SN74HC193N

template <uint32_t W> class counter : public component {
    public:
        input<1> up, down, load, clear ;
        input<W> data_in ;
        output<1> co, bo ;
        output<W> data_out ;
    private:
        uint32_t _cnt ;
        uint8_t _prev_up, _prev_down ;

    public:
        counter() : up(this), down(this), load(this), clear(this), data_in(this) {
            _cnt = 0 ;
            co = 1 ;
            bo = 1 ;
            _prev_up = 1 ;
            _prev_down = 1 ;
        } ;

        operator uint32_t(){
            return _cnt ;
        }

        void always(){
            if (clear){
                _cnt = 0 ;
            }
            
            if (load){
                _cnt = data_in ;
            }

            if ((up)&&(! _prev_up)){
                _cnt = (_cnt + 1) & ((1 << W) - 1) ;
            }
            _prev_up = up ;
            co = (((! up)&&(_cnt == ((1 << W) - 1))) ? 0 : 1) ;

            if ((down)&&(! _prev_down)){
                _cnt = (_cnt - 1) & ((1 << W) - 1) ;
            }
            _prev_down = down ;
            bo = (((! down)&&(_cnt == 0)) ? 0 : 1) ;

            data_out = _cnt ;
        } ;
} ;


#endif