#ifndef ALUH_H
#define ALUH_H


#include "circuit.h"
#include "ALUl.h"


/*
    c_in should come from the C of ALUl
    s_in should come from the S of ALUl
*/
class ALUh : public component {
    public:
        input<1> c_in, s_in, z_in ;
        input<4> a, b ;
        input<4> op ;
        output<4> res ;
        output<1> n, z, c, v ;

    public:
        ALUh() : c_in(this), s_in(this), z_in(this), a(this), b(this), op(this) {
        } ;

        void always(){
            uint8_t vb = b ;

            switch (op.get_value()){
                case ALU_ADD:
                case ALU_ADC: {
                    uint32_t tmp = a + b + c_in ;
                    res = tmp ;
                    c = tmp >> 4 ; 
                    break ;
                }
                case ALU_AND: 
                case ALU_BIT: {
                    res = a & b ;
                    c = 0 ; 
                    break ;
                }
                case ALU_ASL: 
                case ALU_ROL: {
                    uint32_t tmp = b << 1 | c_in ;
                    res = tmp ;
                    c = tmp >> 4 ; 
                    break ;
                }
                case ALU_CMP: {
                    uint32_t tmp = a + (~b & 0xF) + c_in ;
                    res = tmp ;
                    c = tmp >> 4 ;
                    break ;
                }
                case ALU_DEC: {
                    uint32_t tmp = b + (~0 & 0xF) + c_in ;
                    res = tmp ;
                    c = tmp >> 4 ;
                    break ;
                }
                case ALU_EOR: {
                    res = a ^ b ;
                    c = 0 ; 
                    break ;
                }
                case ALU_INC: {
                    uint32_t tmp = b + c_in ;
                    res = tmp ;
                    c = tmp >> 4 ;
                    break ;
                }
                case ALU_LSR: {
                    res = b >> 1 ;
                    c = s_in ; 
                    break ;
                }
                case ALU_ORA: {
                    res = a | b ;
                    c = 0 ; 
                    break ;
                }
                case ALU_ROR: {
                    res = c_in << 3 | b >> 1 ;
                    c = s_in ; 
                    break ;
                }
                case ALU_SBC: {
                    vb = ~b & 0xF ;
                    uint32_t tmp = a + vb + c_in ;
                    res = tmp ;
                    c = tmp >> 4 ;
                    break ;
                }
                case ALU_PASS: {
                    res = b ;
                    c = 0 ; 
                    break ;
                }
                case ALU_INTV: {
                    res = 0xFF ;
                    c = 0 ; 
                    break ;
                }
            }

            z = (((z_in == 1)&&(res == 0)) ? 1 : 0) ;
            if (op == ALU_BIT){
                v = b >> 2 ;
                n = b >> 3 ;
            }
            else {
                v = ((a^res) & (vb^res)) >> 3 ;
                n = res >> 3 ;
            }
        } ;
} ;


#endif