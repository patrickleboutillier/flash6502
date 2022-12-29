#ifndef CTRL_OUT_H
#define CTRL_OUT_H


#include "circuit.h"

#define CLK_ASYNC  1
#define CLK_SYNC   2
#define STEP_CLR   3
#define RAM_S      5
#define INST_S     6
#define PC_UP      4
#define PC_CLR     7


// Simulates a SN74HC138
class CTRL_OUT : public component {
    public:
        input<3> cmd ;
        output<1> CLK_async, CLK_sync, RAM_s, PC_up, STEP_clr, INST_s, PC_clr ;
    private:
        output<3> *_src ;

    public:
        CTRL_OUT(output<3> *src) :  cmd(this),
                                    CLK_async(1), CLK_sync(1), RAM_s(1), PC_up(1), STEP_clr(1), INST_s(1), PC_clr(1) {
            _src = src ;
            _src->connect(cmd) ;
        } ;


        void always(){
            CLK_async = (cmd == CLK_ASYNC ? 0 : 1) ;
            CLK_sync = (cmd == CLK_SYNC ? 0 : 1) ;
            STEP_clr = (cmd == STEP_CLR ? 0 : 1) ;
            RAM_s = (cmd == RAM_S ? 0 : 1) ;
            INST_s = (cmd == INST_S ? 0 : 1) ;
            PC_up = (cmd == PC_UP ? 0 : 1) ;
            PC_clr = (cmd == PC_CLR ? 0 : 1) ;
        } ;


        void pulse(uint8_t cmd){
            (*_src) = cmd ;
            (*_src) = 0 ;            
        }
} ;


#endif