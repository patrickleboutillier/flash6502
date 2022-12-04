// unittest_SimpleMath.cpp : Defines the entry point for the console application.

#include "gtest/gtest.h"
#include "ALU.h"


static int calc_v(int a, int b, uint32_t res){
    return ((((a & 0xFF)^(res & 0xFF)) & ((b & 0xFF)^(res & 0xFF))) >> 7) & 1 ;
}


TEST(test_pl6502, ALU){
    output<8> a, b ;
    output<1> cy ;
    output<4> op ;
    ALU alu ;
    a.connect(alu.a) ;
    b.connect(alu.b) ;
    cy.connect(alu.c_in) ;
    op.connect(alu.op) ;

    op = ALU_ADC ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 256 ; i++){
            for (int j = 0 ; j < 256 ; j++){
                a = i ; b = j ; cy = k ;
                uint32_t res = i + j + k ;
                EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
                EXPECT_EQ(alu.c.get_value(), (res >> 8) & 1) ;
                EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
                EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
                EXPECT_EQ(alu.v.get_value(), calc_v(i, j, res)) ;
            }
        }
    }

    op = ALU_ADD ;
    for (int i = 0 ; i < 256 ; i++){
        for (int j = 0 ; j < 256 ; j++){
            a = i ; b = j ;
            uint32_t res = i + j ;
            EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
            EXPECT_EQ(alu.c.get_value(), (res >> 8) & 1) ;
            EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
            EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
            EXPECT_EQ(alu.v.get_value(), calc_v(i, j, res)) ;
        }
    }

    op = ALU_AND ;
    for (int i = 0 ; i < 256 ; i++){
        for (int j = 0 ; j < 256 ; j++){
            a = i ; b = j ; 
            uint32_t res = i & j ;
            EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
            EXPECT_EQ(alu.c.get_value(), 0) ;
            EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
            EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
            EXPECT_EQ(alu.v.get_value(), calc_v(i, j, res)) ;
        }
    }

    op = ALU_BIT ;
    for (int i = 0 ; i < 256 ; i++){
        for (int j = 0 ; j < 256 ; j++){
            a = i ; b = j ; 
            uint32_t res = i & j ;
            EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
            EXPECT_EQ(alu.c.get_value(), 0) ;
            EXPECT_EQ(alu.n.get_value(), (j >> 7) & 1) ;
            EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
            EXPECT_EQ(alu.v.get_value(), (j >> 6) & 1) ;
        }
    }

    op = ALU_CMP ;
    for (int i = 0 ; i < 256 ; i++){
        for (int j = 0 ; j < 256 ; j++){
            a = i ; b = j ;
            uint32_t res = i - j ;
            EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
            EXPECT_EQ(alu.c.get_value(), (i >= j ? 1 : 0)) ;
            EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
            EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
            EXPECT_EQ(alu.v.get_value(), calc_v(i, j, res)) ;
        }
    }

    op = ALU_DEC ;
    for (int i = 0 ; i < 256 ; i++){
        b = i ;
        uint32_t res = i - 1 ;
        EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
        EXPECT_EQ(alu.c.get_value(), (i >= 1 ? 1 : 0)) ;
        EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
        EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
    }

    op = ALU_EOR ;
    for (int i = 0 ; i < 256 ; i++){
        for (int j = 0 ; j < 256 ; j++){
            a = i ; b = j ; 
            uint32_t res = i ^ j ;
            EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
            EXPECT_EQ(alu.c.get_value(), 0) ;
            EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
            EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
            EXPECT_EQ(alu.v.get_value(), calc_v(i, j, res)) ;
        }
    }

    op = ALU_INC ;
    for (int i = 0 ; i < 256 ; i++){
        b = i ;
        uint32_t res = i + 1 ;
        EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
        EXPECT_EQ(alu.c.get_value(), (res >> 8) & 1) ;
        EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
        EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
    }

    op = ALU_LSR ;
    for (int i = 0 ; i < 256 ; i++){
        b = i ;
        //printf("i=%d\n", i) ;
        uint32_t res = i >> 1 ;
        EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
        EXPECT_EQ(alu.c.get_value(), i & 1) ;
        EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
        EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
    }

    op = ALU_ORA ;
    for (int i = 0 ; i < 256 ; i++){
        for (int j = 0 ; j < 256 ; j++){
            a = i ; b = j ; 
            uint32_t res = i | j ;
            EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
            EXPECT_EQ(alu.c.get_value(), 0) ;
            EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
            EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
            EXPECT_EQ(alu.v.get_value(), calc_v(i, j, res)) ;
        }
    }

    op = ALU_ROL ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 256 ; i++){
            b = i ; cy = k ;
            uint32_t res = i << 1 | k ;
            EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
            EXPECT_EQ(alu.c.get_value(), (res >> 8) & 1) ;
            EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
            EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
        }
    }

    op = ALU_ROR ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 256 ; i++){
            b = i ; cy = k ;
            //printf("i=%d, k=%d\n", i, k) ;
            uint32_t res = k << 7 | i >> 1 ;
            EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
            EXPECT_EQ(alu.c.get_value(), i & 1) ;
            EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
            EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
        }
    }

    op = ALU_SBC ;
    for (int k = 0 ; k < 2 ; k++){
        for (int i = 0 ; i < 256 ; i++){
            for (int j = 0 ; j < 256 ; j++){
                //printf("i=%d, j=%d, k=%d\n", i, j, k) ;
                a = i ; b = j ; cy = k ;
                uint32_t res = i - j + k - 1 ;
                EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
                EXPECT_EQ(alu.c.get_value(), ((i + (k - 1)) >= j ? 1 : 0)) ;
                EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
                EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
                EXPECT_EQ(alu.v.get_value(), calc_v(i, ~((uint8_t)j), res)) ;
            }
        }
    }

    op = ALU_PASS ;
    for (int i = 0 ; i < 16 ; i++){
        b = i ;
        uint32_t res = i ;
        EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
        EXPECT_EQ(alu.c.get_value(), 0) ;
        EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
        EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
    }


    op = ALU_SXT ;
    for (int i = 0 ; i < 256 ; i++){
        b = i ;
        uint32_t res = (b < 128 ? 0 : 0xFF) ;
        EXPECT_EQ(alu.res.get_value(), res & 0xFF) ;
        EXPECT_EQ(alu.c.get_value(), 0) ;
        EXPECT_EQ(alu.n.get_value(), (res & 0b10000000 ? 1 : 0)) ;
        EXPECT_EQ(alu.z.get_value(), ((res & 0xFF) == 0 ? 1 : 0)) ;
    }
}