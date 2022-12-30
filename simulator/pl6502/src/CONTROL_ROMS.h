#ifndef CONTROL_ROMS_H
#define CONTROL_ROMS_H


#include "circuit.h"
#include "../../src/microcode.h"


#define set_signal_1(output, bit) if (((cw >> bit) & 0x1) != ((prev >> bit) & 0x1)){ output = (cw >> bit) & 0x1 ; }
#define set_signal_4(output, bit) if (((cw >> bit) & 0xF) != ((prev >> bit) & 0xF)){ output = (cw >> bit) & 0xF ; }


class CONTROL_1_ROM : public component {
    public:
        input<8> inst ;
        input<1> n, v, z, c ;
        input<6> step ;
        output<1> X_s, X_e, Y_s, Y_e, ACC_s, ACC_e, A_s, INST_done ;

        CONTROL_1_ROM() :   inst(this), n(this), v(this), z(this), c(this), step(this),
                            X_e(1), Y_e(1), ACC_e(1) {
        } ;

        uint8_t make_cw(){
            return 
                INST_done   << 7 |
                X_e         << 6 |
                Y_e         << 5 |
                ACC_e       << 4 |
                X_s         << 3 |
                Y_s         << 2 |
                ACC_s       << 1 |
                A_s         << 0 ;
        }

        void always(const void *trigger){
            uint8_t prev = make_cw() ;
            uint8_t cw = (microcode[inst << 10 | n << 9 | v << 8 | z << 7 | c << 6 | step] >> 0) & 0xFF ;

            set_signal_1(INST_done, 7) ;
            set_signal_1(X_e,       6) ;
            set_signal_1(Y_e,       5) ;
            set_signal_1(ACC_e,     4) ;
            set_signal_1(X_s,       3) ;
            set_signal_1(Y_s,       2) ;
            set_signal_1(ACC_s,     1) ;
            set_signal_1(A_s,       0) ;
        } ;
} ;


class CONTROL_2_ROM : public component {
    public:
        input<8> inst ;
        input<1> n, v, z, c ;
        input<6> step ;
        output<1> SP_down, SP_s, SP_e, INST_s, PC_up, PC_e, RAM_s, RAM_e ;

        CONTROL_2_ROM() :   inst(this), n(this), v(this), z(this), c(this), step(this),
                            SP_down(1), SP_s(1), SP_e(1), PC_up(1), PC_e(1), RAM_s(1), RAM_e(1) {
        } ;

        uint8_t make_cw(){
            return 
                SP_down << 7 |
                SP_s    << 6 |
                SP_e    << 5 |
                PC_up   << 4 |
                PC_e    << 3 |
                INST_s  << 2 |
                RAM_s   << 1 |
                RAM_e   << 0 ;
        }

        void always(const void *trigger){
            uint8_t prev = make_cw() ;
            uint8_t cw = (microcode[inst << 10 | n << 9 | v << 8 | z << 7 | c << 6 | step] >> 8) & 0xFF ;

            set_signal_1(SP_down,   7) ;
            set_signal_1(SP_s,      6) ;
            set_signal_1(SP_e,      5) ;
            
            // PC_up for reset sequence.
            if (! n){
                PC_up = 0 ;
            }
            else {
                set_signal_1(PC_up, 4) ;
            }

            // PC_e for reset sequence.
            if (! v){
                PC_e = 0 ;
            }
            else {
                set_signal_1(PC_e,  3) ;
            }

            // INST_s for reset sequence and interrupts
            if (z){
                INST_s = 1 ;
            }
            else {
                set_signal_1(INST_s, 2) ;
            }
            
            // RAM_s for reset sequence.
            if (! c){
                RAM_s = 0 ;
            }
            else {
                set_signal_1(RAM_s, 1) ;
            }
            
            set_signal_1(RAM_e,     0) ;
        } ;
} ;


class CONTROL_3_ROM : public component {
    public:
        input<8> inst ;
        input<1> n, v, z, c ;
        input<6> step ;
        output<4> ALU_op ; 
        output<1> ALU_e, ST_e, ST_src, B_s ;

        CONTROL_3_ROM() :   inst(this), n(this), v(this), z(this), c(this), step(this), 
                            ALU_e(1), ST_e(1), ST_src(1)  {
        } ;

        uint8_t make_cw(){
            return 
                ALU_op  << 4 |
                ALU_e   << 3 |
                B_s     << 2 |
                ST_e    << 1 |
                ST_src  << 0 ;
        }

        void always(const void *trigger){
            uint8_t prev = make_cw() ;
            uint8_t cw = (microcode[inst << 10 | n << 9 | v << 8 | z << 7 | c << 6 | step] >> 16) & 0xFF ;

            set_signal_4(ALU_op,    4) ; 
            set_signal_1(ALU_e,     3) ;
            set_signal_1(B_s,       2) ; 
            set_signal_1(ST_e,      1) ; 
            set_signal_1(ST_src,    0) ;
        } ;
} ;


class CONTROL_4_ROM : public component {
    public:
        input<8> inst ;
        input<1> n, v, z, c ;
        input<6> step ;
        output<1> Ah2D_e, EAl_s, Al2D_e, EAh_s, EAh_e, PCh_s, EAl_e, PCl_s ;

        CONTROL_4_ROM() :   inst(this), n(this), v(this), z(this), c(this), step(this), 
                            Ah2D_e(1), Al2D_e(1), EAh_e(1), PCh_s(1), EAl_e(1), PCl_s(1) {
        } ;

        // TODO: Rearrange signal order for optimal layout.
        uint8_t make_cw(){
            return 
                EAl_e  << 7 |
                Al2D_e << 6 |
                Ah2D_e << 5 |
                EAh_e  << 4 |
                PCl_s  << 3 |
                EAl_s  << 2 |
                EAh_s  << 1 |
                PCh_s  << 0 ;               
        }

        void always(const void *trigger){
            uint8_t prev = make_cw() ;
            uint8_t cw = (microcode[inst << 10 | n << 9 | v << 8 | z << 7 | c << 6 | step] >> 24) & 0xFF ;

            set_signal_1(EAl_e, 7) ;
            set_signal_1(Al2D_e, 6) ;
            set_signal_1(Ah2D_e, 5) ;
            set_signal_1(EAh_e, 4) ;
            set_signal_1(PCl_s, 3) ;
            set_signal_1(EAl_s, 2) ;
            set_signal_1(EAh_s, 1) ;
            set_signal_1(PCh_s, 0) ;
        } ;
} ;


class CONTROL_5_ROM : public component {
    public:
        input<8> inst ;
        input<1> n, v, z, c ;
        input<6> step ;
        output<1> ST_bi, ST_NZ_s, ST_I_s, ST_V_s, ST_C_s, ST_ALU_C_s, ST_ALU_C_from_C, ST_s ;

        CONTROL_5_ROM() :   inst(this), n(this), v(this), z(this), c(this), step(this) {
        } ;

        uint8_t make_cw(){
            return 
                ST_bi           << 7 |
                ST_NZ_s         << 6 |
                ST_V_s          << 5 |
                ST_I_s          << 4 |
                ST_C_s          << 3 |
                ST_ALU_C_s      << 2 |
                ST_ALU_C_from_C << 1 |
                ST_s            << 0 ;
        }

        void always(const void *trigger){
            uint8_t prev = make_cw() ;
            uint8_t cw = (microcode[inst << 10 | n << 9 | v << 8 | z << 7 | c << 6 | step] >> 32) & 0xFF ;

            set_signal_1(ST_bi,             7) ;
            set_signal_1(ST_NZ_s,           6) ;
            set_signal_1(ST_V_s,            5) ;
            set_signal_1(ST_I_s,            4) ;
            set_signal_1(ST_C_s,            3) ;
            set_signal_1(ST_ALU_C_s,        2) ;
            set_signal_1(ST_ALU_C_from_C,   1) ;
            set_signal_1(ST_s,              0) ;
        } ;
} ;


// Helper class
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

    uint64_t get_cw(uint8_t inst, uint8_t flags, uint8_t step){
        uint64_t cw = microcode[inst << 10 | flags << 6 | step] ;
        return cw ;
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


#endif
