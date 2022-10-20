#ifndef ALU_H
#define ALU_H


#include "circuit.h"
#include "buffer.h"
#include "ALUl.h"
#include "ALUh.h"


class ALU : public component {
    public:
        input<1> C ;
        input<8> a, b ;
        input<4> op ;
        output<8> res ;
        output<1> n, z, c, v ;
        input<1> ci_set, ci_C_or_c ;
    private:
        ALUl alul ;
        output<1> alul_c_in, alul_s_in ;
        output<4> alul_a, alul_b ;
        ALUh aluh ;
        output<1> aluh_c_in, aluh_s_in, aluh_z_in ;
        output<4> aluh_a, aluh_b ;
        reg<1> ci ;
        output<1> ci_e, ci_s, ci_data_in ;

    public:
        ALU() : C(this), a(this), b(this), op(this), ci_set(this), ci_C_or_c(this) {
            alul_c_in.connect(alul.c_in) ;
            alul_s_in.connect(alul.s_in) ;
            alul_a.connect(alul.a) ;
            alul_b.connect(alul.b) ;
            aluh_c_in.connect(aluh.c_in) ;
            aluh_s_in.connect(aluh.s_in) ;
            aluh_z_in.connect(aluh.z_in) ;
            aluh_a.connect(aluh.a) ;
            aluh_b.connect(aluh.b) ;

            ci_data_in.connect(ci.data_in) ;
            ci_s.connect(ci.set) ;
            ci_e.connect(ci.enable) ;
            ci_e = 1 ; 
            // TODO ci.data_out.connect(alu_c_in) ; 
        } ;

        void always(){
            ci_data_in = (ci_C_or_c == 0 ? C : c) ;
            ci_s = ci_set ;

            alul.op = op ;
            aluh.op = op ;
            alul_a = a & 0xF ;
            aluh_a = a >> 4 ;
            alul_b = b & 0xF ;
            aluh_b = b >> 4 ;
            // TODO comment this line
            alul_c_in = C ;
            aluh_c_in = alul.c ;
            alul_s_in = b >> 4 ;
            aluh_s_in = alul.s ;
            aluh_z_in = alul.z ;
            // ...
            res = aluh.res << 4 | alul.res ;
            n = aluh.n ;
            z = aluh.z ;
            c = aluh.c ;
            v = aluh.v ;
        } ;
} ;


#endif