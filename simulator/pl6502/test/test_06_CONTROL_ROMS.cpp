// unittest_SimpleMath.cpp : Defines the entry point for the console application.

#include "gtest/gtest.h"
#include "CONTROL_ROMS.h"


TEST(test_pl6502, CONTROL_1_ROM){
    output<8> inst ;
    output<1> n, v, z, c ;
    output<6> step ;
    CONTROL_1_ROM crtl_rom ;
    inst.connect(crtl_rom.inst) ;
    n.connect(crtl_rom.n) ;
    v.connect(crtl_rom.v) ;
    z.connect(crtl_rom.z) ;
    c.connect(crtl_rom.c) ;
    step.connect(crtl_rom.step) ;
}


TEST(test_pl6502, CONTROL_2_ROM){
    output<8> inst ;
    output<1> n, v, z, c ;
    output<6> step ;
    CONTROL_2_ROM crtl_rom ;
    inst.connect(crtl_rom.inst) ;
    n.connect(crtl_rom.n) ;
    v.connect(crtl_rom.v) ;
    z.connect(crtl_rom.z) ;
    c.connect(crtl_rom.c) ;
    step.connect(crtl_rom.step) ;
}


TEST(test_pl6502, CONTROL_3_ROM){
    output<8> inst ;
    output<1> n, v, z, c ;
    output<6> step ;
    CONTROL_3_ROM crtl_rom ;
    inst.connect(crtl_rom.inst) ;
    n.connect(crtl_rom.n) ;
    v.connect(crtl_rom.v) ;
    z.connect(crtl_rom.z) ;
    c.connect(crtl_rom.c) ;
    step.connect(crtl_rom.step) ;
}


TEST(test_pl6502, CONTROL_4_ROM){
    output<8> inst ;
    output<1> n, v, z, c ;
    output<6> step ;
    CONTROL_4_ROM crtl_rom ;
    inst.connect(crtl_rom.inst) ;
    n.connect(crtl_rom.n) ;
    v.connect(crtl_rom.v) ;
    z.connect(crtl_rom.z) ;
    c.connect(crtl_rom.c) ;
    step.connect(crtl_rom.step) ;
}


TEST(test_pl6502, CONTROL_5_ROM){
    output<8> inst ;
    output<1> n, v, z, c ;
    output<6> step ;
    CONTROL_5_ROM crtl_rom ;
    inst.connect(crtl_rom.inst) ;
    n.connect(crtl_rom.n) ;
    v.connect(crtl_rom.v) ;
    z.connect(crtl_rom.z) ;
    c.connect(crtl_rom.c) ;
    step.connect(crtl_rom.step) ;
}