#ifndef COUNTER_H
#define COUNTER_H


#include "circuit.h"

/* 
SN74HC193N (up/down)
- Negative LOAD
- The outputs of the four flip-flops are triggered on a low-to-high-level transition of either count (clock) input (UP
or DOWN). The direction of counting is determined by which count input is pulsed while the other count input
is high.
- A clear (CLR) input has been provided that forces all outputs to the low level when a high level is applied. The
clear function is independent of the count and LOAD inputs.
*/  
template <uint32_t W> class counter_updown : public component {
    public:
        input<1> up, down, load, clear ;
        input<W> data_in ;
        output<1> co, bo ;
        output<W> data_out ;
    private:
        uint32_t _cnt ;
        uint8_t _prev_up, _prev_down ;

    public:
        counter_updown() : up(this), down(this), load(this), clear(this), data_in(this) {
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
            
            if (! load){
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


/*
SN74HC161
- Negative LOAD
- A low level at the clear (CLR) input sets all four of the flip-flop outputs low, regardless of the levels of the CLK, load (LOAD), or enable inputs.
- Both ENP and ENT must be high to count
- Changes at control inputs (ENP, ENT, or LOAD) that modify the operating mode have no effect on the contents of the counter until clocking occurs.
*/  
template <uint32_t W> class counter : public component {
    public:
        input<1> clk, load, clear, enable ;
        input<W> data_in ;
        output<1> rco ;
        output<W> data_out ;
    private:
        uint32_t _cnt ;
        uint8_t _prev_clk ;

    public:
        counter() : clk(this), load(this), clear(this), enable(this), data_in(this) {
            _cnt = 0 ;
            rco = 0 ;
            _prev_clk = 1 ;
        } ;

        operator uint32_t(){
            return _cnt ;
        }

        void always(){
            if (! clear){
                _cnt = 0 ;
            }
            
            if (! load){
                _cnt = data_in ;
            }

            if (enable){
                if ((clk)&&(! _prev_clk)){
                    _cnt = (_cnt + 1) & ((1 << W) - 1) ;
                    rco = ((_cnt == ((1 << W) - 1)) ? 1 : 0) ;
                }
                _prev_clk = clk ;
            }

            data_out = _cnt ;
        } ;
} ;


#endif
