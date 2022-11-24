// unittest_SimpleMath.cpp : Defines the entry point for the console application.

#include "gtest/gtest.h"
#include "CONTROL_ROMS.h"


TEST(test_pl6502, CONTROL_1_ROM){
    output<8> inst ;
    output<1> n, v, z, c ;
    output<4> step ;
    output<2> phase ; 
    CONTROL_1_ROM ctrl1_rom ;
    inst.connect(ctrl1_rom.inst) ;
    n.connect(ctrl1_rom.n) ;
    v.connect(ctrl1_rom.v) ;
    z.connect(ctrl1_rom.z) ;
    c.connect(ctrl1_rom.c) ;
    step.connect(ctrl1_rom.step) ;
    phase.connect(ctrl1_rom.phase) ;
}


TEST(test_pl6502, CONTROL_2_ROM){
    output<8> inst ;
    output<1> n, v, z, c ;
    output<4> step ;
    output<2> phase ; 
    CONTROL_2_ROM ctrl2_rom ;
    inst.connect(ctrl2_rom.inst) ;
    n.connect(ctrl2_rom.n) ;
    v.connect(ctrl2_rom.v) ;
    z.connect(ctrl2_rom.z) ;
    c.connect(ctrl2_rom.c) ;
    step.connect(ctrl2_rom.step) ;
    phase.connect(ctrl2_rom.phase) ;
}