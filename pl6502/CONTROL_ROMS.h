#ifndef CONTROL_ROMS_H
#define CONTROL_ROMS_H


#include "circuit.h"
#ifndef MICROCODE_H
#define MICROCODE_H
#include "../microcode.h"
#endif


class CONTROL_1_ROM : public component {
    public:
        input<8> inst ;
        input<1> n, v, z, c ;
        input<4> step ;
        input<2> phase ;
        output<1> X_s, X_e, Y_s, Y_e, ACC_s, ACC_e ;

        CONTROL_1_ROM() :   inst(this), n(this), v(this), z(this), c(this), step(this), phase(this),
                            X_e(1), Y_e(1), ACC_e(1) {
        } ;

        uint8_t make_cw(){
            return 
                X_s << 0 |
                X_e << 1 |
                Y_s << 2 |
                Y_e << 3 |
                ACC_s << 4 |
                ACC_e << 5 ;
        }

        void always(){
            uint8_t prev = make_cw() ;
            uint8_t cw = (microcode[inst << 10 | n << 9 | v << 8 | z << 7 | c << 6 | step << 2 | phase] >> 0) & 0xFF ;

            #define set_signal_1(output, bit) if (((cw >> bit) & 0x1) != ((prev >> bit) & 0x1)){ output = cw >> bit ; }

            set_signal_1(X_s, 0) ;
            set_signal_1(X_e, 1) ;
            set_signal_1(Y_s, 2) ;
            set_signal_1(Y_e, 3) ;
            set_signal_1(ACC_s, 4) ;
            set_signal_1(ACC_e, 5) ;
        } ;
} ;


class CONTROL_2_ROM : public component {
    public:
        input<8> inst ;
        input<1> n, v, z, c ;
        input<4> step ;
        input<2> phase ;
        output<1> SP_down, SP_s, SP_e, EAl_s, EAl_e, PC_up, PCl_s, PC_e ;

        CONTROL_2_ROM() :   inst(this), n(this), v(this), z(this), c(this), step(this), phase(this),
                            SP_down(1), SP_e(1), EAl_e(1), PC_up(1), PC_e(1)  {
        } ;

        uint8_t make_cw(){
            return 
                SP_down << 0 |
                SP_s << 1 |
                SP_e << 2 |
                EAl_s << 3 |
                EAl_e << 4 |
                PC_up << 5 |
                PCl_s << 6 |
                PC_e  << 7 ;
        }

        void always(){
            uint8_t prev = make_cw() ;
            uint8_t cw = (microcode[inst << 10 | n << 9 | v << 8 | z << 7 | c << 6 | step << 2 | phase] >> 8) & 0xFF ;

            #define set_signal_1(output, bit) if (((cw >> bit) & 0x1) != ((prev >> bit) & 0x1)){ output = cw >> bit ; }

            set_signal_1(SP_down, 0) ;
            set_signal_1(SP_s, 1) ;
            set_signal_1(SP_e, 2) ;
            set_signal_1(EAl_s, 3) ;
            set_signal_1(EAl_e, 4) ;
            set_signal_1(PC_up, 5) ;
            set_signal_1(PCl_s, 6) ;
            set_signal_1(PC_e, 7) ;
        } ;
} ;


class CONTROL_3_ROM : public component {
    public:
        input<8> inst ;
        input<1> n, v, z, c ;
        input<4> step ;
        input<2> phase ;
        output<4> ALU_op ; 
        output<1> A_s, ALU_e, B_s ;

        CONTROL_3_ROM() :   inst(this), n(this), v(this), z(this), c(this), step(this), phase(this),
                            ALU_e(1)  {
        } ;

        uint8_t make_cw(){
            return 
                ALU_op << 0 | 
                A_s << 4 |
                ALU_e << 5 | 
                B_s << 6 ;
        }

        void always(){
            uint8_t prev = make_cw() ;
            uint8_t cw = (microcode[inst << 10 | n << 9 | v << 8 | z << 7 | c << 6 | step << 2 | phase] >> 16) & 0xFF ;

            #define set_signal_1(output, bit) if (((cw >> bit) & 0x1) != ((prev >> bit) & 0x1)){ output = cw >> bit ; }
            #define set_signal_4(output, bit) if (((cw >> bit) & 0xF) != ((prev >> bit) & 0xF)){ output = cw >> bit ; }

            set_signal_4(ALU_op, 0) ; 
            set_signal_1(A_s, 4) ;
            set_signal_1(ALU_e, 5) ; 
            set_signal_1(B_s, 6) ;
        } ;
} ;

#endif