#ifndef STATUS_H
#define STATUS_H


#include "circuit.h"
#include "reg.h"
#include "STATUS_ROM.h"

/*
    Connections:
        - Data bus (for input and output)
        - ALU flags (ALU.n, ALU.v, ALU.z, ALU.c)

    Control signals:
        - nz_set, v_set, c_set, alu_c_set
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
        input<1> n_in, v_in, z_in, c_in, i_in ;
        input<1> nz_set, v_set, c_set, i_set, alu_c_set, alu_c_from_C, src_data ;
        input<1> set ;
        input<8> data_in ;
        input<1> data_enable ;
        output<1> N, V, Z, C, I, alu_c ;
        output<8> data_out ;
        reg<8> sreg ;
    private:
        STATUS_ROM srom ;
        output<1> srom_n_in, srom_v_in, srom_z_in, srom_c_in, srom_i_in ;
        output<1> srom_nz_set, srom_v_set, srom_c_set, srom_i_set, srom_alu_c_set, srom_alu_c_from_C ;
        output<1> srom_n_old, srom_v_old, srom_z_old, srom_c_old, srom_i_old, srom_alu_c_old ;
        output<1> sreg_enable, sreg_set ;
        output<8> sreg_data_in ;
    public:
        STATUS() : n_in(this),   v_in(this),  z_in(this), c_in(this), i_in(this), 
                   nz_set(this), v_set(this), c_set(this), i_set(this), alu_c_set(this), alu_c_from_C(this),
                   src_data(this), set(this), data_in(this), data_enable(this), 
                   sreg_enable(1) {
            sreg_set.connect(sreg.set) ;
            sreg_enable.connect(sreg.enable) ;
            sreg_data_in.connect(sreg.data_in) ;
            sreg_enable = 0 ; // always enabled

            srom_n_old.connect(srom.n_old) ;
            srom_v_old.connect(srom.v_old) ;
            srom_z_old.connect(srom.z_old) ;
            srom_c_old.connect(srom.c_old) ;
            srom_i_old.connect(srom.i_old) ;
            srom_alu_c_old.connect(srom.alu_c_old) ;
            
            srom_n_in.connect(srom.n_in) ;
            srom_v_in.connect(srom.v_in) ;
            srom_z_in.connect(srom.z_in) ;
            srom_c_in.connect(srom.c_in) ;
            srom_i_in.connect(srom.i_in) ;
            srom_nz_set.connect(srom.nz_set) ;
            srom_v_set.connect(srom.v_set) ;
            srom_c_set.connect(srom.c_set) ;
            srom_i_set.connect(srom.i_set) ;
            srom_alu_c_set.connect(srom.alu_c_set) ;
            srom_alu_c_from_C.connect(srom.alu_c_from_C) ;
            data_out.drive(false) ;
        } ;

        void always(){ 
            sreg_data_in = srom.I << 5 | srom.N << 4 | srom.V << 3 | srom.Z << 2 |  srom.C << 1 | srom.alu_c ; 

            sreg_set = set ;

            srom_i_old = sreg.data_out >> 5 ;
            srom_n_old = sreg.data_out >> 4 ;
            srom_v_old = sreg.data_out >> 3 ;
            srom_z_old = sreg.data_out >> 2 ;
            srom_c_old = sreg.data_out >> 1 ;
            srom_alu_c_old = sreg.data_out ;

            srom_nz_set = nz_set ;
            srom_v_set = v_set ;
            srom_c_set = c_set ;
            srom_i_set = i_set ;
            srom_alu_c_set = alu_c_set ;
            srom_alu_c_from_C = alu_c_from_C ;

            // This can be implemented using a 2-1 multiplexer
            if (src_data){
                // Drive srom_*_in from the data bus
                srom_n_in = data_in >> 7 ;
                srom_v_in = data_in >> 6 ;
                srom_i_in = data_in >> 2 ;
                srom_z_in = data_in >> 1 ;
                srom_c_in = data_in ;
            }
            else {
                // Drive srom_*_in from the flag inputs
                srom_n_in = n_in ;
                srom_v_in = v_in ;
                srom_z_in = z_in ;
                srom_c_in = c_in ;
                srom_i_in = i_in ;
            }

            I = sreg.data_out >> 5 ;
            N = sreg.data_out >> 4 ;
            V = sreg.data_out >> 3 ;
            Z = sreg.data_out >> 2 ;
            C = sreg.data_out >> 1 ;
            alu_c = sreg.data_out ;
 
            if (! data_enable){
                // This can be implemented with a 373 with the set always on 
                data_out.drive(true) ;
                uint8_t P = N << 7 | V << 6 | 1 << 5 | 1 << 4 | I << 2 | Z << 1 | C ;
                data_out.set_value(P) ;
            }
            else {
                data_out.drive(false) ;
            }
        } ;
} ;


#endif