// unittest_SimpleMath.cpp : Defines the entry point for the console application.

#include "gtest/gtest.h"
#include "circuit.h"


class dummy : public component {
    public:
        input<1> i ;
        dummy() : i(this){} ;
        void always(){} ;
} ;


TEST(test_circuit, output){	
    output<1> o ;
    EXPECT_EQ(0, o.get_value()) ;

    dummy d ;
    o.connect(d.i) ;
    EXPECT_EQ(d.i._driver, &o) ;
    o = 0 ;
    EXPECT_EQ(d.i.get_value(), o.get_value()) ;
    o = 1 ;
    EXPECT_EQ(d.i.get_value(), o.get_value()) ;
    o.drive(false) ;
    EXPECT_EQ(d.i._driver, nullptr) ;
    o.drive(true) ;
    EXPECT_EQ(d.i._driver, &o) ;
}