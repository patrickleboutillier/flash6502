// unittest_SimpleMath.cpp : Defines the entry point for the console application.

#include "gtest/gtest.h"
#include "STATUS.h"


TEST(test_pl6502, STATUS){
    output<1> n_in, v_in, d_in, i_in, z_in, c_in, b_in ;
    output<1> nz_set, v_set, d_set, i_set, c_set ;
    output<8> data_in, src_data ;
    output<1> data_enable ;
    STATUS status ;
    n_in.connect(status.n_in) ;
    v_in.connect(status.v_in) ;
    d_in.connect(status.d_in) ;
    i_in.connect(status.i_in) ;
    z_in.connect(status.z_in) ;
    c_in.connect(status.c_in) ;
    b_in.connect(status.b_in) ;
    nz_set.connect(status.nz_set) ;
    v_set.connect(status.v_set) ;
    d_set.connect(status.d_set) ;
    i_set.connect(status.i_set) ;
    c_set.connect(status.c_set) ;
    data_in.connect(status.data_in) ;
    src_data.connect(status.src_data) ;
    data_enable.connect(status.data_enable) ;

    // Normal operation mode, whth data_enable
    data_enable = 1 ;
    for (int i = 0 ; i < 4096 ; i++){
        uint32_t n_old = status.N ;
        uint32_t v_old = status.V ;
        uint32_t d_old = status.D ;
        uint32_t i_old = status.I ;
        uint32_t z_old = status.Z ;
        uint32_t c_old = status.C ;
        n_in = i >> 11 ;
        v_in = i >> 10 ;
        d_in = i >> 9 ;
        i_in = i >> 8 ;
        z_in = i >> 7 ;
        c_in = i >> 6 ;
        b_in = i >> 5 ;
        nz_set = i >> 4 ;
        v_set = i >> 3 ;
        d_set = i >> 2 ;
        i_set = i >> 1 ;
        c_set = i >> 0 ;

        EXPECT_EQ(status.N.get_value(), (nz_set ? n_in.get_value() : n_old)) ;
        EXPECT_EQ(status.V.get_value(), (v_set ? v_in.get_value() : v_old)) ;
        EXPECT_EQ(status.B.get_value(), b_in.get_value()) ;
        EXPECT_EQ(status.D.get_value(), (d_set ? d_in.get_value() : d_old)) ;
        EXPECT_EQ(status.I.get_value(), (i_set ? i_in.get_value() : i_old)) ;
        EXPECT_EQ(status.C.get_value(), (c_set ? c_in.get_value() : c_old)) ;
        EXPECT_EQ(status.Z.get_value(), (nz_set ? z_in.get_value() : z_old)) ;
        uint8_t P = status.N << 7 | status.V << 6 | 1 << 5 | status.B << 4 | 
            status.D << 3 | status.I << 2 | status.Z << 1 | status.C ;
        EXPECT_EQ(status.data_out.get_value(), P) ;

        // Reset the set signals or else they may still be on when we set in inputs 
        // in the next test...
        nz_set = 0 ;
        v_set = 0 ;
        d_set = 0 ;
        i_set = 0 ;
        c_set = 0 ;
    }

    for (int i = 0 ; i < 256 ; i++){
        data_in = i ;
        src_data = 1 ;
        nz_set = 1 ;
        v_set = 1 ;
        d_set = 1 ;
        i_set = 1 ;
        c_set = 1 ;

        EXPECT_EQ(status.data_out.get_value(), i | 1 << 5) ;
        
         // Reset the set signals or else they may still be on when we set in inputs 
        // in the next test...
        nz_set = 0 ;
        v_set = 0 ;
        d_set = 0 ;
        i_set = 0 ;
        c_set = 0 ;       
        src_data = 0 ;
    }
}