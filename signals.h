#ifndef MICROCODE_H
#define MICROCODE_H
#include "microcode.h"
#endif
#include "CONTROL_ROMS.h"


class CONTROL_UNIT {
    private:
        uint64_t _default ;
        CONTROL_1_ROM *_C1 ;
        CONTROL_2_ROM *_C2 ;
        CONTROL_3_ROM *_C3 ;
        CONTROL_4_ROM *_C4 ;
        CONTROL_5_ROM *_C5 ;
        
    public:
      CONTROL_UNIT(CONTROL_1_ROM *c1, CONTROL_2_ROM *c2, CONTROL_3_ROM *c3, CONTROL_4_ROM *c4, CONTROL_5_ROM *c5) {

        _C1 = c1 ;
        _C2 = c2 ;
        _C3 = c3 ;
        _C4 = c4 ;
        _C5 = c5 ;
        _default = make_cw() ;
    }

    uint64_t get_default_cw(){
        return _default ; 
    }

    uint64_t get_cw(uint8_t inst, uint8_t flags, uint8_t step, uint8_t phase){
        uint64_t cw = microcode[inst << 10 | flags << 6 | step << 2 | phase] ;
        return cw ;
    }

    void apply_cw(uint64_t cw){
    }

    uint64_t make_cw(){
        return
            (uint64_t)_C1->make_cw() << 0 | 
            (uint64_t)_C2->make_cw() << 8 |
            (uint64_t)_C3->make_cw() << 16 |
            (uint64_t)_C4->make_cw() << 24 |
            (uint64_t)_C5->make_cw() << 32 ;
    }
} ;