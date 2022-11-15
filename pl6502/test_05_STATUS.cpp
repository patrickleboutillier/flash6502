// unittest_SimpleMath.cpp : Defines the entry point for the console application.

#include "gtest/gtest.h"
#include "STATUS.h"


TEST(test_pl6502, STATUS){
    output<1> n_in, v_in, i_in, z_in, c_in, b_in ;
    output<1> nz_set, v_set, i_set, c_set, alu_c_set, alu_c_from_C ;
    output<8> data_in ;
    output<1> data_enable, src_data, status_set ;
    STATUS status ;
    n_in.connect(status.n_in) ;
    v_in.connect(status.v_in) ;
    z_in.connect(status.z_in) ;
    c_in.connect(status.c_in) ;
    b_in.connect(status.b_in) ;
    nz_set.connect(status.nz_set) ;
    v_set.connect(status.v_set) ;
    c_set.connect(status.c_set) ;
    alu_c_set.connect(status.alu_c_set) ;
    alu_c_from_C.connect(status.alu_c_from_C) ;
    data_in.connect(status.data_in) ;
    src_data.connect(status.src_data) ;
    data_enable.connect(status.data_enable) ;
    status_set.connect(status.set) ;

    // Normal operation mode, with data_enable
    data_enable = 1 ;
    for (int i = 0 ; i < 2048 ; i++){
        uint32_t n_old = status.N ;
        uint32_t v_old = status.V ;
        uint32_t z_old = status.Z ;
        uint32_t c_old = status.C ;
        uint32_t alu_c_old = status.alu_c ;
        n_in = i >> 9 ;
        v_in = i >> 8 ;
        z_in = i >> 7 ;
        c_in = i >> 6 ;
        b_in = i >> 5 ;
        nz_set = i >> 4 ;
        v_set = i >> 3 ;
        c_set = i >> 2 ;
        alu_c_from_C = i >> 1 ;
        alu_c_set = i >> 0 ;

        status_set = 1 ;
        status_set = 0 ;

        EXPECT_EQ(status.N.get_value(), (nz_set ? n_in.get_value() : n_old)) ;
        EXPECT_EQ(status.V.get_value(), (v_set ? v_in.get_value() : v_old)) ;
        EXPECT_EQ(status.C.get_value(), (c_set ? c_in.get_value() : c_old)) ;
        EXPECT_EQ(status.alu_c.get_value(), (alu_c_set ? (alu_c_from_C ? c_old : c_in.get_value()) : alu_c_old)) ;
        EXPECT_EQ(status.Z.get_value(), (nz_set ? z_in.get_value() : z_old)) ;
        uint32_t P = status.N << 7 | status.V << 6 | 1 << 5 | b_in << 4 | 
            status.Z << 1 | status.C ;
        EXPECT_EQ(status.data_out.get_value(), P) ;

        // Reset the set signals or else they may still be on when we set in inputs 
        // in the next test...
        nz_set = 0 ;
        v_set = 0 ;
        c_set = 0 ;
        alu_c_set = 0 ;
    }

    /*
    SN74HC244:
    
      VCC    20E    1Y1    2A4    1Y2    2A3    1Y3    2A2    1Y4    2A1
      10E    1A1    2Y4    1A2    2Y3    1A3    2Y2    1A4    2Y1    GND
                                                 
                    0out3  Bin    0out2  1in    Vout6  Cin    Nout7  Zin
             0in    Bout4  0in    1out5  Vin    Cout0  Nin    Zout1  
    */
    for (int i = 0 ; i < 512 ; i++){
        uint8_t data = i >> 1 ;
        data_in = data ;
        b_in = i ;

        src_data = 1 ;
        nz_set = 1 ;
        v_set = 1 ;
        c_set = 1 ;

        status_set = 1 ;
        status_set = 0 ;
        
        // One bit 5 because it is constant, zero-out bits 2,3 (D,I,B) because they will always be 0, add b_in
        uint32_t p = ((data | 0b00100000) & 0b11100011) | (b_in << 4) ;
        EXPECT_EQ(status.data_out.get_value(), p) ;
        
        // Reset the set signals or else they may still be on when we set in inputs 
        // in the next test...
        nz_set = 0 ;
        v_set = 0 ;
        c_set = 0 ;       
        src_data = 0 ;
    }
}
