#ifndef ALUL_H
#define ALUL_H


#include "circuit.h"

#define ALU_ADC  0
#define ALU_AND  1
#define ALU_BIT  2
#define ALU_CMP  3
#define ALU_DEC  4
#define ALU_EOR  5
#define ALU_INC  6
#define ALU_LSR  7
#define ALU_ORA  8
#define ALU_ROL  9
#define ALU_ROR  10
#define ALU_SBC  11
#define ALU_PASS 12
#define ALU_ADD  13
#define ALU_SXT  14
#define ALU_ASL  15


/*
    c should go to the c_in of ALUh.
    s_in should come from the LSB of ALUh.a
    s should go to the s_in on ALUh in order to be sent to c when required

    TODO: Add PASS for A passthru?
*/
class ALUl : public component {
    public:
        input<1> c_in, s_in, n_in ;
        input<4> a, b ;
        input<4> op ;
        output<4> res ;
        output<1> z, c, s ;

    public:
        ALUl() : c_in(this), s_in(this), n_in(this), a(this), b(this), op(this) {
        } ;

        void always(){
            switch (op.get_value()){
                case ALU_ADC: {
                    uint32_t tmp = a + b + c_in ;
                    res = tmp ;
                    c = tmp >> 4 ; 
                    s = 0 ;
                    break ;
                }
                case ALU_ADD: {
                    uint32_t tmp = a + b ;
                    res = tmp ;
                    c = tmp >> 4 ; 
                    s = 0 ;
                    break ;
                }
                case ALU_AND: 
                case ALU_BIT: {
                    res = a & b ;
                    c = 0 ; 
                    s = 0 ;
                    break ;
                }
                case ALU_ASL: {
                    uint32_t tmp = b << 1 ;
                    res = tmp ;
                    c = tmp >> 4 ; 
                    s = 0 ;
                    break ;
                }
                case ALU_CMP: {
                    uint32_t tmp = a + (~b & 0xF) + 1 ;
                    res = tmp ;
                    c = tmp >> 4 ; 
                    s = 0 ;
                    break ;
                }
                case ALU_DEC: {
                    uint32_t tmp = b + (~1 & 0xF) + 1 ;
                    res = tmp ;
                    c = tmp >> 4 ; 
                    s = 0 ;
                    break ;
                }
                case ALU_EOR: {
                    res = a ^ b ;
                    c = 0 ; 
                    s = 0 ;
                    break ;
                }
                case ALU_INC: {
                    uint32_t tmp = b + 1 ;
                    res = tmp ;
                    c = tmp >> 4 ;
                    s = 0 ;
                    break ;
                }
                case ALU_LSR: {
                    res = s_in << 3 | b >> 1 ;
                    c = 0 ; 
                    s = b ;
                    break ;
                }
                case ALU_ORA: {
                    res = a | b ;
                    c = 0 ; 
                    s = 0 ;
                    break ;
                }
                case ALU_ROL: {
                    uint32_t tmp = b << 1 | c_in ;
                    res = tmp ;
                    c = tmp >> 4 ; 
                    s = 0 ;
                    break ;
                }
                case ALU_ROR: {
                    res = s_in << 3 | b >> 1 ;
                    c = c_in ; 
                    s = b ;
                    break ;
                }
                case ALU_SBC: {
                    uint32_t tmp = a + (~b & 0xF) + c_in ;
                    res = tmp ;
                    c = tmp >> 4 ; 
                    s = 0 ;
                    break ;
                }
                case ALU_PASS: {
                    res = b ;
                    c = 0 ; 
                    s = 0 ;
                    break ;
                }
                case ALU_SXT: {
                    res = (n_in ? 0xF : 0) ;
                    c = 0 ;
                    s = 0 ;
                    break ;
                }
            }

            z = (res == 0 ? 1 : 0) ;
        } ;
} ;


#endif