#ifndef STATUS_H
#define STATUS_H

#include "hdl/bus.h"
#include "hdl/buf.h"
#include "hdl/sensor.h" 
#include "DATA.h"

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

#define STATUS_ADDR_OLD_N     17
#define STATUS_ADDR_OLD_V     16
#define STATUS_ADDR_OLD_D     15
#define STATUS_ADDR_OLD_I     14
#define STATUS_ADDR_OLD_Z     13
#define STATUS_ADDR_OLD_C     12

#define STATUS_ADDR_N     11
#define STATUS_ADDR_V     10
#define STATUS_ADDR_D      9
#define STATUS_ADDR_I      8
#define STATUS_ADDR_Z      7
#define STATUS_ADDR_C      6

#define STATUS_ADDR_SET_NZ 5
#define STATUS_ADDR_SET_V  4
#define STATUS_ADDR_SET_D  3
#define STATUS_ADDR_SET_I  2
// #define STATUS_ADDR_SET_Z  1
#define STATUS_ADDR_SET_C  0

#define STATUS_DATA_N      7
#define STATUS_DATA_V      6
#define STATUS_DATA_D      3
#define STATUS_DATA_I      2
#define STATUS_DATA_Z      1
#define STATUS_DATA_C      0


class STATUS : public sensor {
    public:
        bus addr ;
        bus data ;
        buf N, V, D, I, Z, C ;
        wire B, enable, fromDATA ;
    private:
        DATA *_DATA ;

    public:
        STATUS(DATA *d) : addr(18, 0), data(8, 0), 
            N(data.bit(STATUS_DATA_N), addr.bit(STATUS_ADDR_OLD_N)), 
            V(data.bit(STATUS_DATA_V), addr.bit(STATUS_ADDR_OLD_V)), 
            D(data.bit(STATUS_DATA_D), addr.bit(STATUS_ADDR_OLD_D)),
            I(data.bit(STATUS_DATA_I), addr.bit(STATUS_ADDR_OLD_I)), 
            Z(data.bit(STATUS_DATA_Z), addr.bit(STATUS_ADDR_OLD_Z)), 
            C(data.bit(STATUS_DATA_C), addr.bit(STATUS_ADDR_OLD_C)){
            _DATA = d ;
            add_signal(&addr) ;
            add_signal(&B) ;
            add_signal(&enable) ;
            add_signal(&fromDATA) ;
            always() ;
        }


        void always() {
            uint8_t d = 0b00100000 ;
            if (fromDATA.v()){
                d |= (_DATA->data.v() & 0b11001111) ; // Ignore break
            }
            else {
                d |= (addr.bit(STATUS_ADDR_SET_NZ)->v() ? addr.bit(STATUS_ADDR_N)->v() : addr.bit(STATUS_ADDR_OLD_N)->v()) << 7 ; // N
                d |= (addr.bit(STATUS_ADDR_SET_V)->v()  ? addr.bit(STATUS_ADDR_V)->v() : addr.bit(STATUS_ADDR_OLD_V)->v()) << 6 ; // V
                d |= (addr.bit(STATUS_ADDR_SET_D)->v()  ? addr.bit(STATUS_ADDR_D)->v() : addr.bit(STATUS_ADDR_OLD_D)->v()) << 3 ; // D
                d |= (addr.bit(STATUS_ADDR_SET_I)->v()  ? addr.bit(STATUS_ADDR_I)->v() : addr.bit(STATUS_ADDR_OLD_I)->v()) << 2 ; // I
                d |= (addr.bit(STATUS_ADDR_SET_NZ)->v() ? addr.bit(STATUS_ADDR_Z)->v() : addr.bit(STATUS_ADDR_OLD_Z)->v()) << 1 ; // Z
                d |= (addr.bit(STATUS_ADDR_SET_C)->v()  ? addr.bit(STATUS_ADDR_C)->v() : addr.bit(STATUS_ADDR_OLD_C)->v()) << 0 ; // C
            }
            data.v(d) ;
            if (enable.v()){
                d |= (B.v() << 4) ;
                _DATA->data.v(d) ;
            }
        }
} ;


#endif