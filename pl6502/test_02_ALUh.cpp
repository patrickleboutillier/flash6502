// unittest_SimpleMath.cpp : Defines the entry point for the console application.

#include "gtest/gtest.h"
#include "ALUh.h"


static int calc_v(int a, int b, uint32_t res){
    return ((((a & 0xF)^(res & 0xF)) & ((b & 0xF)^(res & 0xF))) >> 3) & 1 ;
}


TEST(test_pl6502, ALUh){
    output<4> a, b ;
    output<1> cy, shr, z ;
    output<4> op ;
    ALUh aluh ;
    a.connect(aluh.a) ;
    b.connect(aluh.b) ;
    cy.connect(aluh.c_in) ;
    shr.connect(aluh.s_in) ;
    z.connect(aluh.z_in) ;
    op.connect(aluh.op) ;

    // We do not test z flag here, we will test it in the complete ALU tests
    
    op = ALU_ADC ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 16 ; i++){
            for (int j = 0 ; j < 16 ; j++){
                a = i ; b = j ; cy = k ;
                uint32_t res = i + j + k ;
                EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
                EXPECT_EQ(aluh.c.get_value(), (res >> 4) & 1) ;
                EXPECT_EQ(aluh.n.get_value(), (res & 0b1000 ? 1 : 0)) ;
                EXPECT_EQ(aluh.v.get_value(), calc_v(i, j, res)) ;
            }
        }
    }

    op = ALU_AND ;
    for (int i = 0 ; i < 16 ; i++){
        for (int j = 0 ; j < 16 ; j++){
            a = i ; b = j ; 
            uint32_t res = i & j ;
            EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
            EXPECT_EQ(aluh.c.get_value(), 0) ;
            EXPECT_EQ(aluh.n.get_value(), (res & 0b1000 ? 1 : 0)) ;
            EXPECT_EQ(aluh.v.get_value(), calc_v(i, j, res)) ;
        }
    }

    op = ALU_BIT ;
    for (int i = 0 ; i < 16 ; i++){
        for (int j = 0 ; j < 16 ; j++){
            a = i ; b = j ; 
            uint32_t res = i & j ;
            EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
            EXPECT_EQ(aluh.c.get_value(), 0) ;
            EXPECT_EQ(aluh.n.get_value(), (j >> 3) & 1) ;
            EXPECT_EQ(aluh.v.get_value(), (j >> 2) & 1) ;
        }
    }

    op = ALU_CMP ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 16 ; i++){
            for (int j = 0 ; j < 16 ; j++){
                a = i ; b = j ; cy = k ;
                uint32_t res = i - j + k - 1 ;
                EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
                EXPECT_EQ(aluh.c.get_value(), ((i + (k - 1)) >= j ? 1 : 0)) ;
                EXPECT_EQ(aluh.n.get_value(), (res & 0b1000 ? 1 : 0)) ;
                EXPECT_EQ(aluh.v.get_value(), calc_v(i, j, res)) ;
            }
        }
    }

    op = ALU_DEC ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 16 ; i++){
            b = i ; cy = k ;
            uint32_t res = i + (k - 1) ;
            EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
            EXPECT_EQ(aluh.c.get_value(), ((i + (k - 1)) >= 0 ? 1 : 0)) ;
            EXPECT_EQ(aluh.n.get_value(), (res & 0b1000 ? 1 : 0)) ;
        }
    }

    op = ALU_EOR ;
    for (int i = 0 ; i < 16 ; i++){
        for (int j = 0 ; j < 16 ; j++){
            a = i ; b = j ; 
            uint32_t res = i ^ j ;
            EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
            EXPECT_EQ(aluh.c.get_value(), 0) ;
            EXPECT_EQ(aluh.n.get_value(), (res & 0b1000 ? 1 : 0)) ;
            EXPECT_EQ(aluh.v.get_value(), calc_v(i, j, res)) ;
        }
    }

    op = ALU_INC ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 16 ; i++){
            b = i ; cy = k ;
            uint32_t res = i + k ;
            EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
            EXPECT_EQ(aluh.c.get_value(), (res >> 4) & 1) ;
            EXPECT_EQ(aluh.n.get_value(), (res & 0b1000 ? 1 : 0)) ;
        }
    }

    op = ALU_LSR ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 16 ; i++){
            b = i ; shr = k ;
            uint32_t res = i >> 1 ;
            EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
            EXPECT_EQ(aluh.c.get_value(), k) ;
            EXPECT_EQ(aluh.n.get_value(), (res & 0b1000 ? 1 : 0)) ;
        }
    }

    op = ALU_ORA ;
    for (int i = 0 ; i < 16 ; i++){
        for (int j = 0 ; j < 16 ; j++){
            a = i ; b = j ; 
            uint32_t res = i | j ;
            EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
            EXPECT_EQ(aluh.c.get_value(), 0) ;
            EXPECT_EQ(aluh.n.get_value(), (res & 0b1000 ? 1 : 0)) ;
            EXPECT_EQ(aluh.v.get_value(), calc_v(i, j, res)) ;
        }
    }

    op = ALU_ROL ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 16 ; i++){
            b = i ; cy = k ;
            uint32_t res = i << 1 | k ;
            EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
            EXPECT_EQ(aluh.c.get_value(), (res >> 4) & 1) ;
            EXPECT_EQ(aluh.n.get_value(), (res & 0b1000 ? 1 : 0)) ;
        }
    }

    op = ALU_ROR ;
    for (int m = 0 ; m < 2 ; m++){
        for (int k = 0 ; k < 2 ; k++){
            for (int i = 0 ; i < 16 ; i++){
                b = i ; shr = k ; cy = m ;
                uint32_t res = m << 3 | i >> 1 ;
                EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
                EXPECT_EQ(aluh.c.get_value(), k) ;
                EXPECT_EQ(aluh.n.get_value(), (res & 0b1000 ? 1 : 0)) ;
            }
        }
    }

    op = ALU_SBC ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 16 ; i++){
            for (int j = 0 ; j < 16 ; j++){
                a = i ; b = j ; cy = k ;
                uint32_t res = i - j + (k - 1) ;
                EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
                EXPECT_EQ(aluh.c.get_value(), ((i + (k - 1)) >= j ? 1 : 0)) ;
                EXPECT_EQ(aluh.n.get_value(), (res & 0b1000 ? 1 : 0)) ;
                EXPECT_EQ(aluh.v.get_value(), calc_v(i, ~((uint8_t)j), res)) ;
            }
        }
    }

    op = ALU_PASS ;
    for (int i = 0 ; i < 16 ; i++){
        b = i ;
        uint32_t res = i ;
        EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
        EXPECT_EQ(aluh.c.get_value(), 0) ;
        EXPECT_EQ(aluh.n.get_value(), (res & 0b1000 ? 1 : 0)) ;
    }


    /*
        SST39SF020A: 
            VDD WE# A17 A14 A13 A8  A9  A11 OE# A10 CE# DQ7 DQ6 DQ5 DQ4 DQ3
            NC  A16 A15 A12 A7  A6  A5  A4  A3  A2  A1  A0  DQ0 DQ1 DQ2 VSS

            a:                  A16, A15, A12, A7
            b:                  A3,  A2,  A1,  A0
            op:                 A13, A8, A9, A11
            c_in, s_in, z_in:   A10, A17, A14     
            res:                DQ3, DQ2, DQ1, DQ0
            n, z, c, s:         DQ7, DQ6, DQ5, DQ4
    */

    // Final run to generate ROM file
    FILE *rom = fopen("ALUH_ROM.bin","wb") ;
    #define bit(b) ((addr >> (b)) & 0x01)
    uint32_t max = 1 << 18 ; // Flash has 18 address bits
    for (uint32_t addr = 0 ; addr < max ; addr++){
        a =  bit(16) << 3 | bit(15) << 2 | bit(12) << 1 | bit(7) ;
        b =  bit(3)  << 3 | bit(2)  << 2 | bit(1)  << 1 | bit(0) ;
        op = bit(13) << 3 | bit(8)  << 2 | bit(9)  << 1 | bit(11) ;
        cy = bit(10) ;
        shr = bit(17) ;
        z = bit(14) ;

        uint8_t data = aluh.n << 7 | aluh.z << 6 | aluh.c << 5 | aluh.v << 4 | aluh.res ;
        fwrite(&data, 1, 1, rom) ;
    }}