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

    op = ALU_ASL ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 16 ; i++){
            b = i ; cy = k ;
            uint32_t res = i << 1 | k ;
            EXPECT_EQ(aluh.res.get_value(), res & 0xF) ;
            EXPECT_EQ(aluh.c.get_value(), (res >> 4) & 1) ;
            EXPECT_EQ(aluh.n.get_value(), (res & 0b1000 ? 1 : 0)) ;
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
}