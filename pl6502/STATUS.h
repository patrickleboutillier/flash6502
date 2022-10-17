#ifndef STATUS_H
#define STATUS_H


#include "circuit.h"
#include "STATUS_ROM.h"

/*
    Connections:
        - Data bus (for input and output)
        - ALU flags (ALU.n, ALU,v, ALU,z, ALU,c)

    Control signals:
        - nz_set, v_set, i_set, c_set
        - i_in, b_in
        - src_data, data_enable
*/

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

class STATUS : public component {
    public:
        input<1> n_in, v_in, i_in, z_in, c_in, b_in ;
        input<1> nz_set, v_set, i_set, c_set, src_data ;
        input<8> data_in ;
        input<1> data_enable ;
        output<1> N, V, B, I, Z, C ;
        output<8> data_out ;
    private:
        STATUS_ROM rom ;
        output<1> sr_n_in, sr_v_in, sr_i_in, sr_z_in, sr_c_in, sr_b_in ;
        output<1> sr_nz_set, sr_v_set, sr_i_set, sr_c_set ;
    public:
        STATUS() : n_in(this),   v_in(this),  i_in(this),  z_in(this), c_in(this), b_in(this),
                   nz_set(this), v_set(this), i_set(this), c_set(this),
                   src_data(this), data_in(), data_enable(this){
            sr_n_in.connect(rom.n_in) ;
            sr_v_in.connect(rom.v_in) ;
            sr_i_in.connect(rom.i_in) ;
            sr_z_in.connect(rom.z_in) ;
            sr_c_in.connect(rom.c_in) ;
            sr_b_in.connect(rom.b_in) ; 
            sr_nz_set.connect(rom.nz_set) ;
            sr_v_set.connect(rom.v_set) ;
            sr_i_set.connect(rom.i_set) ;
            sr_c_set.connect(rom.c_set) ;
            data_out.drive(false) ;
        } ;

        void always(){
            sr_nz_set = nz_set ;
            sr_v_set = v_set ;
            sr_i_set = i_set ;
            sr_c_set = c_set ;

            // This can be implemented using a 2-1 multiplexer
            if (src_data){
                // Drive sr_*_in from the data bus
                sr_n_in = data_in >> 7 ;
                sr_v_in = data_in >> 6 ;
                sr_b_in = data_in >> 4 ;
                sr_i_in = data_in >> 2 ;
                sr_z_in = data_in >> 1 ;
                sr_c_in = data_in ;
            }
            else {
                // Drive sr_*_in from the flag inputs
                sr_n_in = n_in ;
                sr_v_in = v_in ;
                sr_b_in = b_in ;
                sr_i_in = i_in ;
                sr_z_in = z_in ;
                sr_c_in = c_in ;
            }

            N = rom.N ;
            V = rom.V ;
            B = rom.B ;
            I = rom.I ;
            Z = rom.Z ;
            C = rom.C ;

            if (data_enable){
                // This can be implemented with a 373 with the set always on 
                data_out.drive(true) ;
                uint8_t P = N << 7 | V << 6 | 1 << 5 | B << 4 | I << 2 | Z << 1 | C ;
                data_out.set_value(P) ;
            }
            else {
                data_out.drive(false) ;
            }
        } ;
} ;


#endif