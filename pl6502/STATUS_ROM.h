#ifndef STATUS_ROM_H
#define STATUS_ROM_H


#include "circuit.h"

/*
    SR Flags (bit 7 to bit 0)
    N	Negative
    V	Overflow
    -	ignored
    B	Break
    D	Decimal (use BCD for arithmetics)
    I	Interrupt (IRQ disable)
    Z	Zero
    C	Carry
*/

class STATUS_ROM : public component {
    public:
        input<1> n_in, v_in, z_in, c_in ;
        input<1> nz_set, v_set, c_set, alu_c_set, alu_c_from_C ;
        output<1> N, V, Z, C, alu_c ;
        input<1> n_old, v_old, z_old, c_old, alu_c_old ;

    public:
        STATUS_ROM() : n_old(this),  v_old(this), z_old(this), c_old(this), alu_c_old(this),
                       nz_set(this), v_set(this), c_set(this), alu_c_set(this), alu_c_from_C(this) {
        } ;

        void always(){
            N = (nz_set ? n_in : n_old) ;
            V = (v_set ? v_in : v_old) ;
            Z = (nz_set ? z_in : z_old) ;
            C = (c_set ? c_in : c_old) ;
            alu_c = (alu_c_set ? (alu_c_from_C ? c_old : c_in) : alu_c_old) ;
        } ;
} ;


#endif
