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
        input<1> n_old, v_old, d_old, i_old, z_old, c_old ;
        input<1> n_in, v_in, d_in, i_in, z_in, c_in, b_in ;
        input<1> nz_set, v_set, d_set, i_set, c_set ;
        output<1> N, V, B, D, I, Z, C ;

    public:
        STATUS_ROM() : n_old(this), v_old(this), d_old(this), i_old(this), z_old(this), c_old(this), {
                       n_in(this),  v_in(this),  d_in(this),  i_in(this),  z_in(this), c_in(this, )b_in(this),
                       nz_set(this), v_set(this), d_set(this), i_set(this), c_set(this){
            N.connect(n_old) ;
            V.connect(v_old) ;
            D.connect(d_old) ;
            I.connect(i_old) ;
            Z.connect(z_old) ;
            C.connect(c_old) ;
        } ;

        void always(){
            N = (nz_set ? n_in : n_old) ;
            //p |= (addr.bit(STATUS_ADDR_SET_V)->v()  ? addr.bit(STATUS_ADDR_V)->v() : addr.bit(STATUS_ADDR_OLD_V)->v()) << 6 ; // V
            //p |= (addr.bit(STATUS_ADDR_SET_D)->v()  ? addr.bit(STATUS_ADDR_D)->v() : addr.bit(STATUS_ADDR_OLD_D)->v()) << 3 ; // D
            //p |= (addr.bit(STATUS_ADDR_SET_I)->v()  ? addr.bit(STATUS_ADDR_I)->v() : addr.bit(STATUS_ADDR_OLD_I)->v()) << 2 ; // I
            //p |= (addr.bit(STATUS_ADDR_SET_NZ)->v() ? addr.bit(STATUS_ADDR_Z)->v() : addr.bit(STATUS_ADDR_OLD_Z)->v()) << 1 ; // Z
            //p |= (addr.bit(STATUS_ADDR_SET_C)->v()  ? addr.bit(STATUS_ADDR_C)->v() : addr.bit(STATUS_ADDR_OLD_C)->v()) << 0 ; // C
        } ;
} ;


#endif