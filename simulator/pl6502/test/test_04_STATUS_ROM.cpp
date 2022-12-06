// unittest_SimpleMath.cpp : Defines the entry point for the console application.

#include "gtest/gtest.h"
#include "STATUS_ROM.h"


TEST(test_pl6502, STATUS_ROM){
    output<1> n_in, v_in, z_in, c_in ;
    output<1> n_old, v_old, z_old, c_old, alu_c_old ;
    output<1> nz_set, v_set, c_set, alu_c_set, alu_c_from_C ;
    STATUS_ROM status_rom ;
    n_in.connect(status_rom.n_in) ;
    v_in.connect(status_rom.v_in) ;
    z_in.connect(status_rom.z_in) ;
    c_in.connect(status_rom.c_in) ;
    nz_set.connect(status_rom.nz_set) ;
    v_set.connect(status_rom.v_set) ;
    c_set.connect(status_rom.c_set) ;
    alu_c_set.connect(status_rom.alu_c_set) ;
    alu_c_from_C.connect(status_rom.alu_c_from_C) ;
    n_old.connect(status_rom.n_old) ;
    v_old.connect(status_rom.v_old) ;
    z_old.connect(status_rom.z_old) ;
    c_old.connect(status_rom.c_old) ;
    alu_c_old.connect(status_rom.alu_c_old) ;

    for (int i = 0 ; i < 32768 ; i++){
        n_old = i >> 14 ;
        v_old = i >> 13 ;
        z_old = i >> 12 ;
        c_old = i >> 11 ;
        alu_c_old = i >> 10 ;
        n_in = i >> 9 ;
        v_in = i >> 8 ;
        z_in = i >> 7 ;
        c_in = i >> 6 ;
        nz_set = i >> 4 ;
        v_set = i >> 3 ;
        c_set = i >> 2 ;
        alu_c_from_C = i >> 1 ;
        alu_c_set = i >> 0 ;

        EXPECT_EQ(status_rom.N.get_value(), (nz_set ? n_in.get_value() : n_old.get_value())) ;
        EXPECT_EQ(status_rom.V.get_value(), (v_set ? v_in.get_value() : v_old.get_value())) ;
        EXPECT_EQ(status_rom.C.get_value(), (c_set ? c_in.get_value() : c_old.get_value())) ;
        EXPECT_EQ(status_rom.Z.get_value(), (nz_set ? z_in.get_value() : z_old.get_value())) ;
        EXPECT_EQ(status_rom.alu_c.get_value(), (alu_c_set ? (alu_c_from_C ? c_old.get_value() : c_in.get_value()) : alu_c_old.get_value())) ;

        // Reset the set signals or else they may still be on when we set in inputs 
        // in the next test...
        nz_set = 0 ;
        v_set = 0 ;
        c_set = 0 ;
        alu_c_set = 0 ;
    }

    /*
        SST39SF020A: 
            VDD WE# A17 A14 A13 A8  A9  A11 OE# A10 CE# DQ7 DQ6 DQ5 DQ4 DQ3
            NC  A16 A15 A12 A7  A6  A5  A4  A3  A2  A1  A0  DQ0 DQ1 DQ2 VSS

        n_in, v_in, z_in, c_in, b_in:                   A16, A15, A12, A7, A6
        nz_set, v_set, c_set, alu_c_set, alu_c_from_C:  A4, A3, A2, A1, A0 
        n_old, v_old, z_old, c_old, alu_c_old:          A9, A8,     A13, A14, A17
        N, V, B, Z, C, alu_c:                           D7, D6, D5,  D4,  D3, D2
    */

    // Final run to generate ROM file
    FILE *rom = fopen("STATUS_ROM.bin","wb") ;
    #define bit(b) ((addr >> (b)) & 0x01)
    uint32_t max = 1 << 18 ; // Flash has 18 address bits
    for (uint32_t addr = 0 ; addr < max ; addr++){
        n_in = bit(16) ;
        v_in = bit(15) ;
        z_in = bit(12) ;
        c_in = bit(7) ;

        n_old = bit(9) ;
        v_old = bit(8) ;
        z_old = bit(13) ;
        c_old = bit(14) ;
        alu_c_old = bit(17) ;

        nz_set = bit(4) ;
        v_set = bit(3) ;
        c_set = bit(2) ;
        alu_c_set = bit(1) ;
        alu_c_from_C = bit(0) ;

        // N, V, Z, C, alu_c: D7, D6, D4, D3, D2
        uint8_t data = status_rom.N << 7 | status_rom.V << 6 |  
            status_rom.Z << 4 | status_rom.C << 3 | status_rom.alu_c << 2 ;
 
        fwrite(&data, 1, 1, rom) ;
    }
}