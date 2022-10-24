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
}