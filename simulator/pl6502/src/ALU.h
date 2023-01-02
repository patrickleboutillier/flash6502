#ifndef ALU_H
#define ALU_H


#include "circuit.h"
#include "ALUL_ROM.h"
#include "ALUH_ROM.h"


class ALU : public component {
    public:
        input<1> c_in ;
        input<8> a, b ;
        input<4> op ;
        input<1> enable ;
        output<8> res ;
        output<1> n, z, c, v ;
    private:
        ALUl alul ;
        output<1> alul_c_in, alul_s_in, alul_n_in ;
        output<4> alul_a, alul_b ;
        ALUh aluh ;
        output<1> aluh_c_in, aluh_s_in, aluh_z_in ;
        output<4> aluh_a, aluh_b, alu_op ;

    public:
        ALU() : c_in(this), a(this), b(this), op(this), enable(this) {
            alul_c_in.connect(alul.c_in) ;
            alul_s_in.connect(alul.s_in) ;
            alul_n_in.connect(alul.n_in) ;
            alul_a.connect(alul.a) ;
            alul_b.connect(alul.b) ;
            aluh_c_in.connect(aluh.c_in) ;
            aluh_s_in.connect(aluh.s_in) ;
            aluh_z_in.connect(aluh.z_in) ;
            aluh_a.connect(aluh.a) ;
            aluh_b.connect(aluh.b) ;
            alu_op.connect(alul.op) ;
            alu_op.connect(aluh.op) ;

            res.drive(false) ;
            n.drive(false) ;
            z.drive(false) ;
            c.drive(false) ;
            v.drive(false) ;
        } ;

        void always(const void *trigger){
            alu_op = op ;
            alul_a = a & 0xF ;
            aluh_a = a >> 4 ;
            alul_b = b & 0xF ;
            aluh_b = b >> 4 ;
            alul_c_in = c_in ;      // cy_in    -> A10
            aluh_c_in = alul.c ;    // ALUL.DQ5 -> A10
            alul_s_in = b >> 4 ;    // B[4]     -> A17
            aluh_s_in = alul.s ;    // ALUL.DQ4 -> A17
            aluh_z_in = alul.z ;    // ALUL.DQ6 -> A14
            alul_n_in = b >> 7 ;    // B[7]     -> A14

            // ...
            if (! enable){ // negative logic
                res.drive(true) ;
                n.drive(true) ;
                z.drive(true) ;
                c.drive(true) ;
                v.drive(true) ;

                res = aluh.res << 4 | alul.res ;
                n = aluh.n ;
                z = aluh.z ;
                c = aluh.c ;
                v = aluh.v ;
            }
            else {
                res.drive(false) ;
                n.drive(false) ;
                z.drive(false) ;
                c.drive(false) ;
                v.drive(false) ;
            }
        } ;
} ;


#endif
