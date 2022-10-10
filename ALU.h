#ifndef ROM_H
#define ROM_H

#include "ROM.h"
#include "REG.h"

#define ALU_ROM_ADDR_SRI  14
#define ALU_ROM_ADDR_VI   13
#define ALU_ROM_ADDR_CI   12
#define ALU_ROM_ADDR_O4   11
#define ALU_ROM_ADDR_O3   10
#define ALU_ROM_ADDR_O2    9
#define ALU_ROM_ADDR_O1    8
#define ALU_ROM_ADDR_B3    7
#define ALU_ROM_ADDR_B2    6
#define ALU_ROM_ADDR_B1    5
#define ALU_ROM_ADDR_B0    4
#define ALU_ROM_ADDR_A3    3
#define ALU_ROM_ADDR_A2    2
#define ALU_ROM_ADDR_A1    1
#define ALU_ROM_ADDR_A0    0

#define ALU_ROM_DATA_VO    5
#define ALU_ROM_DATA_CO    4
#define ALU_ROM_DATA_S3    3
#define ALU_ROM_DATA_S2    2
#define ALU_ROM_DATA_S1    1
#define ALU_ROM_DATA_S0    0

#define ALU_OP_ADC         0
#define ALU_OP_ADD         1
#define ALU_OP_INC_B       2
#define ALU_OP_SBC         3
#define ALU_OP_DEC_B       4
#define ALU_OP_AND         5
#define ALU_OP_OR          6
#define ALU_OP_XOR         7
#define ALU_OP_SHL         8
#define ALU_OP_ROL         9
#define ALU_OP_SHR        10
#define ALU_OP_ROR        11
#define ALU_OP_BIT        12


class ALU_ROM : public ROM {
    private:
        bool _high ;
    public:
        ALU_ROM(bool high) : ROM() {
            _high = high ;
        }


        void always() {
            uint8_t a = addr.v() & 0xF ;
            uint8_t b = (addr.v() >> 4) & 0xF ;
            uint8_t op = (addr.v() >> 8) & 0xF ;
            uint8_t ci = (addr.v() >> 12) & 0x1 ;
            uint8_t vi = (addr.v() >> 13) & 0x1 ;
            uint8_t sri = (addr.v() >> 14) & 0x1 ; // nhen high, sri is ci, when low sri is a[4]

            switch (op){
                case ALU_OP_ADC: {
                    data.v(a + b + ci) ; // TODO: Add V flag
                    break ;
                }
                case ALU_OP_ADD:
                    data.v(a + b + (_high ? ci : 0)) ;
                    break ;
                case ALU_OP_INCB:
                    data.v(b + 1 + (_high ? ci : 0)) ;
                    break ;
                case ALU_OP_SBC:
                    data .v(a + (b ^ 0xF) + ci) ;
                    break ;
                case ALU_OP_DECB:
                    data .v(b + (1 ^ 0xF) + ci) ;
                    break ;
                case ALU_OP_AND:
                    data.v(a & b) ;
                    break ;
                case ALU_OP_OR:        
                    data.v(a | b) ;
                    break ;
                case ALU_OP_XOR:
                    data.v(a ^ b) ;
                    break ;
                case ALU_OP_SHL:
                    data.v(a << 1 | (_high ? ci : 0)) ;
                    break ;
                case ALU_OP_ROL:
                    data.v((a << 1) | ci) ;
                    break ;
                case ALU_OP_SHR: {
                    bool co = (_high ? 0 : a & 0x1) ;
                    bool si = (_high ? 0 : sri) ;
                    data.v(co << 4 | si << 3 | a >> 1) ;
                    break ;
                }
                case ALU_OP_ROR: {
                    bool co = (_high ? 0 : a & 0x1) ;
                    bool si = sri ;
                    data.v(co << 4 | si << 3 | a >> 1) ;
                    break ;
                }
                case ALU_OP_BIT: {
                    // P is a, operand in b
                    data.v((_high ? (b & 0b1100) | (a & 0x0011) : a)) ;
                    break ;
                }
            }
        }
} ;



class ALU : public sensor {
    public:
        REG A ;
        REG B ;    
        //REG CI ;
        REG ADD ;
        //REG CO ;
        ALU_ROM H, L ;
        bus op ;
    private:
        bus _A_ALU, _B_ALU, _ALU_ADD ;

    public:
        ALU(DATA *d) : _A_ALU(8), _B_ALU(8), _ALU_ADD(8), A(d->data, &_A_ALU()), B(d->data, &_B_ALU()), ADD(&_ALU_ADD, d->data),
            H(1), L(0), op(4) {
            add_signal(&(A.set)) ;
            add_signal(&(B.set)) ;
        }

        void always(){
            // Prepare addr for L ALU
            uint32_t addr = op.v() << 8 | (_B_ALU.v() & 0xF) << 4 | _A_ALU.v() & 0xF ;
            L.addr.v(addr) ;
        }
}


#endif