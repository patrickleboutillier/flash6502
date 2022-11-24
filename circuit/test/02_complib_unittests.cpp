// unittest_SimpleMath.cpp : Defines the entry point for the console application.

#include "gtest/gtest.h"
#include "buffer.h"
#include "not.h"
#include "and.h"
#include "or.h"
#include "xor.h"
#include "reg.h"
#include "mux2.h"
#include "counter.h"


TEST(test_complib, buffer){
    output<1> in ;
    buffer<1> buf ;
    in.connect(buf.a) ;
    in = 0 ;
    EXPECT_EQ(0, buf.b.get_value()) ;
    in = 1 ;
    EXPECT_EQ(1, buf.b.get_value()) ;
}


TEST(test_complib, not){
    output<1> in ;
    not_<1> n ;
    in.connect(n.a) ;
    in = 0 ;
    EXPECT_EQ(1, n.b.get_value()) ;
    in = 1 ;
    EXPECT_EQ(0, n.b.get_value()) ;
}


TEST(test_complib, and){
    output<1> ina, inb ;
    and_<1> a ;
    ina.connect(a.a) ;
    inb.connect(a.b) ;
    ina = 0 ; inb = 0 ;
    EXPECT_EQ(a.c.get_value(), 0) ;
    ina = 0 ; inb = 1 ;
    EXPECT_EQ(a.c.get_value(), 0) ;
    ina = 1 ; inb = 0 ;
    EXPECT_EQ(a.c.get_value(), 0) ;
    ina = 1 ; inb = 1 ;
    EXPECT_EQ(a.c.get_value(), 1) ;
}


TEST(test_complib, or){
    output<1> ina, inb ;
    or_<1> o ;
    ina.connect(o.a) ;
    inb.connect(o.b) ;
    ina = 0 ; inb = 0 ;
    EXPECT_EQ(o.c.get_value(), 0) ;
    ina = 0 ; inb = 1 ;
    EXPECT_EQ(o.c.get_value(), 1) ;
    ina = 1 ; inb = 0 ;
    EXPECT_EQ(o.c.get_value(), 1) ;
    ina = 1 ; inb = 1 ;
    EXPECT_EQ(o.c.get_value(), 1) ;
}


TEST(test_complib, xor){
    output<1> ina, inb ;
    xor_<1> x ;
    ina.connect(x.a) ;
    inb.connect(x.b) ;
    ina = 0 ; inb = 0 ;
    EXPECT_EQ(x.c.get_value(), 0) ;
    ina = 0 ; inb = 1 ;
    EXPECT_EQ(x.c.get_value(), 1) ;
    ina = 1 ; inb = 0 ;
    EXPECT_EQ(x.c.get_value(), 1) ;
    ina = 1 ; inb = 1 ;
    EXPECT_EQ(x.c.get_value(), 0) ;
}


TEST(test_complib, reg){
    output<8> in ;
    output<1> set, enable(1) ;
    reg<8> r ;
    in.connect(r.data_in) ;
    set.connect(r.set) ;
    enable.connect(r.enable) ;
    buffer<8> b ;
    r.data_out.connect(b.a) ;

    in = 0 ; set = 0 ; enable = 1 ;
    EXPECT_EQ(r.data_out.get_value(), 0) ;
    in = 42 ;
    EXPECT_EQ(r.data_out.get_value(), 0) ;
    set = 1 ;
    EXPECT_EQ(r.data_out.get_value(), 0) ;
    enable = 0 ;
    EXPECT_EQ(r.data_out.get_value(), 42) ;
    EXPECT_EQ(b.a._driver, &(r.data_out)) ;
    EXPECT_EQ(b.a.get_value(), 42) ;
    enable = 1 ;
    EXPECT_EQ(r.data_out.get_value(), 0) ;
    EXPECT_EQ(b.a._driver, nullptr) ;
    in = 250 ; set = 1 ;
    EXPECT_EQ(r.data_out.get_value(), 0) ;
    enable = 0 ;
    EXPECT_EQ(r.data_out.get_value(), 250) ;
}

TEST(test_complib, mux2){
    output<1> ina, inb, sel ;
    mux2<1> m ;
    ina.connect(m.a) ;
    inb.connect(m.b) ;
    sel.connect(m.sel) ;
    ina = 0 ; inb = 0 ; sel = 0 ;
    EXPECT_EQ(m.c.get_value(), 0) ;
    ina = 0 ; inb = 1 ;
    EXPECT_EQ(m.c.get_value(), 0) ;
    ina = 1 ; inb = 0 ;
    EXPECT_EQ(m.c.get_value(), 1) ;
    ina = 1 ; inb = 1 ;
    EXPECT_EQ(m.c.get_value(), 1) ;

    ina = 0 ; inb = 0 ; sel = 1 ;
    EXPECT_EQ(m.c.get_value(), 0) ;
    ina = 0 ; inb = 1 ;
    EXPECT_EQ(m.c.get_value(), 1) ;
    ina = 1 ; inb = 0 ;
    EXPECT_EQ(m.c.get_value(), 0) ;
    ina = 1 ; inb = 1 ;
    EXPECT_EQ(m.c.get_value(), 1) ;
}

TEST(test_complib, counter){
    output<1> up, down, load1, load2, clear1, clear2 ;
    output<4> data_in1, data_in2 ;
    counter<4> c1, c2 ;
    up = 1 ; down = 1 ;
    up.connect(c1.up) ;
    down.connect(c1.down) ;
    load1.connect(c1.load) ;
    data_in1.connect(c1.data_in) ;
    load2.connect(c2.load) ;
    data_in2.connect(c2.data_in) ;
    c1.bo.connect(c2.down) ;
    c1.co.connect(c2.up) ;
    clear1.connect(c1.clear) ;
    clear2.connect(c2.clear) ;
    
    EXPECT_EQ(c1.data_out.get_value(), 0) ;
    EXPECT_EQ(c2.data_out.get_value(), 0) ;
    up = 0 ; up = 1 ;
    EXPECT_EQ(c1.data_out.get_value(), 1) ;
    down = 0 ; down = 1 ;
    EXPECT_EQ(c1.data_out.get_value(), 0) ;
    down = 0 ; down = 1 ;
    EXPECT_EQ(c1.data_out.get_value(), 15) ;
    EXPECT_EQ(c2.data_out.get_value(), 15) ;
    data_in1 = 8 ;
    load1 = 1 ; load1 = 0 ;
    EXPECT_EQ(c1.data_out.get_value(), 8) ;
    up = 0 ; up = 1 ;
    EXPECT_EQ(c1.data_out.get_value(), 9) ;
}