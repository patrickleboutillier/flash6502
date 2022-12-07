// unittest_SimpleMath.cpp : Defines the entry point for the console application.

#include "gtest/gtest.h"
#include "ALUl.h"


TEST(test_pl6502, ALUl){
    output<4> a, b ;
    output<1> cy, shr, neg ;
    output<4> op ;
    ALUl alul ;
    a.connect(alul.a) ;
    b.connect(alul.b) ;
    cy.connect(alul.c_in) ;
    shr.connect(alul.s_in) ;
    neg.connect(alul.n_in) ;
    op.connect(alul.op) ;

    op = ALU_ADC ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 16 ; i++){
            for (int j = 0 ; j < 16 ; j++){
                a = i ; b = j ; cy = k ;
                uint32_t res = i + j + k ;
                EXPECT_EQ(alul.res.get_value(), res & 0xF) ;
                EXPECT_EQ(alul.c.get_value(), (res >> 4) & 1) ;
                EXPECT_EQ(alul.s.get_value(), 0) ;
                EXPECT_EQ(alul.z.get_value(), ((res & 0xF) == 0 ? 1 : 0)) ;
            }
        }
    }

    op = ALU_AND ;
    for (int i = 0 ; i < 16 ; i++){
        for (int j = 0 ; j < 16 ; j++){
            a = i ; b = j ; 
            uint32_t res = i & j ;
            EXPECT_EQ(alul.res.get_value(), res & 0xF) ;
            EXPECT_EQ(alul.c.get_value(), 0) ;
            EXPECT_EQ(alul.s.get_value(), 0) ;
            EXPECT_EQ(alul.z.get_value(), ((res & 0xF) == 0 ? 1 : 0)) ;
        }
    }

    op = ALU_BIT ;
    for (int i = 0 ; i < 16 ; i++){
        for (int j = 0 ; j < 16 ; j++){
            a = i ; b = j ; 
            uint32_t res = i & j ;
            EXPECT_EQ(alul.res.get_value(), res & 0xF) ;
            EXPECT_EQ(alul.c.get_value(), 0) ;
            EXPECT_EQ(alul.s.get_value(), 0) ;
            EXPECT_EQ(alul.z.get_value(), ((res & 0xF) == 0 ? 1 : 0)) ;
        }
    }

    op = ALU_CMP ;
    for (int i = 0 ; i < 16 ; i++){
        for (int j = 0 ; j < 16 ; j++){
            a = i ; b = j ;
            uint32_t res = i - j ;
            EXPECT_EQ(alul.res.get_value(), res & 0xF) ;
            EXPECT_EQ(alul.c.get_value(), (i >= j ? 1 : 0)) ;
            EXPECT_EQ(alul.s.get_value(), 0) ;
            EXPECT_EQ(alul.z.get_value(), ((res & 0xF) == 0 ? 1 : 0)) ;
        }
    }

    op = ALU_DEC ;
    for (int i = 0 ; i < 16 ; i++){
        b = i ;
        uint32_t res = i - 1 ;
        EXPECT_EQ(alul.res.get_value(), res & 0xF) ;
        EXPECT_EQ(alul.c.get_value(), (i >= 1 ? 1 : 0)) ;
        EXPECT_EQ(alul.s.get_value(), 0) ;
        EXPECT_EQ(alul.z.get_value(), ((res & 0xF) == 0 ? 1 : 0)) ;
    }

    op = ALU_EOR ;
    for (int i = 0 ; i < 16 ; i++){
        for (int j = 0 ; j < 16 ; j++){
            a = i ; b = j ; 
            uint32_t res = i ^ j ;
            EXPECT_EQ(alul.res.get_value(), res & 0xF) ;
            EXPECT_EQ(alul.c.get_value(), 0) ;
            EXPECT_EQ(alul.s.get_value(), 0) ;
            EXPECT_EQ(alul.z.get_value(), ((res & 0xF) == 0 ? 1 : 0)) ;
        }
    }

    op = ALU_INC ;
    for (int i = 0 ; i < 16 ; i++){
        b = i ;
        uint32_t res = i + 1 ;
        EXPECT_EQ(alul.res.get_value(), res & 0xF) ;
        EXPECT_EQ(alul.c.get_value(), (res >> 4) & 1) ;
        EXPECT_EQ(alul.s.get_value(), 0) ;
        EXPECT_EQ(alul.z.get_value(), ((res & 0xF) == 0 ? 1 : 0)) ;
    }

    op = ALU_LSR ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 16 ; i++){
            b = i ; shr = k ;
            uint32_t res = k << 3 | i >> 1 ;
            EXPECT_EQ(alul.res.get_value(), res & 0xF) ;
            EXPECT_EQ(alul.c.get_value(), 0) ;
            EXPECT_EQ(alul.s.get_value(), i & 1) ;
            EXPECT_EQ(alul.z.get_value(), ((res & 0xF) == 0 ? 1 : 0)) ;
        }
    }

    op = ALU_ORA ;
    for (int i = 0 ; i < 16 ; i++){
        for (int j = 0 ; j < 16 ; j++){
            a = i ; b = j ; 
            uint32_t res = i | j ;
            EXPECT_EQ(alul.res.get_value(), res & 0xF) ;
            EXPECT_EQ(alul.c.get_value(), 0) ;
            EXPECT_EQ(alul.s.get_value(), 0) ;
            EXPECT_EQ(alul.z.get_value(), ((res & 0xF) == 0 ? 1 : 0)) ;
        }
    }

    op = ALU_ROL ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 16 ; i++){
            b = i ; cy = k ;
            uint32_t res = i << 1 | k ;
            EXPECT_EQ(alul.res.get_value(), res & 0xF) ;
            EXPECT_EQ(alul.c.get_value(), (res >> 4) & 1) ;
            EXPECT_EQ(alul.s.get_value(), 0) ;
            EXPECT_EQ(alul.z.get_value(), ((res & 0xF) == 0 ? 1 : 0)) ;
        }
    }

    op = ALU_ROR ;
    for (int m = 0 ; m < 2 ; m++){
        for (int k = 0 ; k < 2 ; k++){
            for (int i = 0 ; i < 16 ; i++){
                b = i ; shr = k ; cy = m ;
                uint32_t res = k << 3 | i >> 1 ;
                EXPECT_EQ(alul.res.get_value(), res & 0xF) ;
                EXPECT_EQ(alul.c.get_value(), m) ;
                EXPECT_EQ(alul.s.get_value(), i & 1) ;
                EXPECT_EQ(alul.z.get_value(), ((res & 0xF) == 0 ? 1 : 0)) ;
            }
        }
    }

    op = ALU_SBC ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 16 ; i++){
            for (int j = 0 ; j < 16 ; j++){
                a = i ; b = j ; cy = k ;
                uint32_t res = i - j + k - 1 ;
                EXPECT_EQ(alul.res.get_value(), res & 0xF) ;
                EXPECT_EQ(alul.c.get_value(), ((i + (k - 1)) >= j ? 1 : 0)) ;
                EXPECT_EQ(alul.s.get_value(), 0) ;
                EXPECT_EQ(alul.z.get_value(), ((res & 0xF) == 0 ? 1 : 0)) ;
            }
        }
    }

    op = ALU_PASS ;
    for (int i = 0 ; i < 16 ; i++){
        b = i ;
        uint32_t res = i ;
        EXPECT_EQ(alul.res.get_value(), res & 0xF) ;
        EXPECT_EQ(alul.c.get_value(), 0) ;
        EXPECT_EQ(alul.s.get_value(), 0) ;
        EXPECT_EQ(alul.z.get_value(), ((res & 0xF) == 0 ? 1 : 0)) ;
    }

    /*
        SST39SF020A: 
            VDD WE# A17 A14 A13 A8  A9  A11 OE# A10 CE# DQ7 DQ6 DQ5 DQ4 DQ3
            NC  A16 A15 A12 A7  A6  A5  A4  A3  A2  A1  A0  DQ0 DQ1 DQ2 VSS

            a:                  A16, A15, A12, A7
            b:                  A3,  A2,  A1,  A0
            op:                 A13, A8, A9, A11
            c_in, s_in, n_in:   A10, A17, A14     
            res:                DQ3, DQ2, DQ1, DQ0
            z, c, s:            DQ6, DQ5, DQ4
    */

    // Final run to generate ROM file
    FILE *rom = fopen("ALUL_ROM.bin","wb") ;
    #define bit(b) ((addr >> (b)) & 0x01)
    uint32_t max = 1 << 18 ; // Flash has 18 address bits
    for (uint32_t addr = 0 ; addr < max ; addr++){
        a =  bit(16) << 3 | bit(15) << 2 | bit(12) << 1 | bit(7) ;
        b =  bit(3)  << 3 | bit(2)  << 2 | bit(1)  << 1 | bit(0) ;
        op = bit(13) << 3 | bit(8)  << 2 | bit(9)  << 1 | bit(11) ;
        cy = bit(10) ;
        shr = bit(17) ;
        neg = bit(14) ;

        uint8_t data = alul.z << 6 | alul.c << 5 | alul.s << 4 | alul.res ;
        fwrite(&data, 1, 1, rom) ;
    }
}