// unittest_SimpleMath.cpp : Defines the entry point for the console application.

#include "gtest/gtest.h"
#include "STATUS_ROM.h"


TEST(test_pl6502, STATUS_ROM){
    output<1> n_in, v_in, d_in, i_in, z_in, c_in, b_in ;
    output<1> nz_set, v_set, d_set, i_set, c_set ;
    STATUS_ROM status_rom ;
    n_in.connect(status_rom.n_in) ;
    v_in.connect(status_rom.v_in) ;
    d_in.connect(status_rom.d_in) ;
    i_in.connect(status_rom.i_in) ;
    z_in.connect(status_rom.z_in) ;
    c_in.connect(status_rom.c_in) ;
    b_in.connect(status_rom.b_in) ;
    nz_set.connect(status_rom.nz_set) ;
    v_set.connect(status_rom.v_set) ;
    d_set.connect(status_rom.d_set) ;
    i_set.connect(status_rom.i_set) ;
    c_set.connect(status_rom.c_set) ;

    for (int i = 0 ; i < 4096 ; i++){
        uint32_t n_old = status_rom.N ;
        uint32_t v_old = status_rom.V ;
        uint32_t d_old = status_rom.D ;
        uint32_t i_old = status_rom.I ;
        uint32_t z_old = status_rom.Z ;
        uint32_t c_old = status_rom.C ;
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

        EXPECT_EQ(status_rom.N.get_value(), (nz_set ? n_in.get_value() : n_old)) ;
        EXPECT_EQ(status_rom.V.get_value(), (v_set ? v_in.get_value() : v_old)) ;
        EXPECT_EQ(status_rom.B.get_value(), b_in.get_value()) ;
        EXPECT_EQ(status_rom.D.get_value(), (d_set ? d_in.get_value() : d_old)) ;
        EXPECT_EQ(status_rom.I.get_value(), (i_set ? i_in.get_value() : i_old)) ;
        EXPECT_EQ(status_rom.C.get_value(), (c_set ? c_in.get_value() : c_old)) ;
        EXPECT_EQ(status_rom.Z.get_value(), (nz_set ? z_in.get_value() : z_old)) ;

        // Reset the set signals or else they may still be on when we set in inputs 
        // in the next test...
        nz_set = 0 ;
        v_set = 0 ;
        d_set = 0 ;
        i_set = 0 ;
        c_set = 0 ;
    }
}