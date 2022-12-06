#ifndef ALU_H
#define ALU_H

#include "CTRLSIG.h"

#define ALU_ADC  0
#define ALU_AND  1
#define ALU_BIT  2
#define ALU_CMP  3
#define ALU_DEC  4
#define ALU_EOR  5
#define ALU_INC  6
#define ALU_LSR  7
#define ALU_ORA  8
#define ALU_ROL  9
#define ALU_ROR  10
#define ALU_SBC  11
#define ALU_PASS 12
#define ALU_ADD  13
#define ALU_SXT  14
#define ALU_ASL  15


class ALU_OP {
  private:
    CTRLSIG *_o3, *_o2, *_o1, *_o0 ;
    
  public:    
    ALU_OP(CTRLSIG *o3, CTRLSIG *o2, CTRLSIG *o1, CTRLSIG *o0){
      _o3 = o3 ;
      _o2 = o2 ;
      _o1 = o1 ;
      _o0 = o0 ;
    }

    void setup(){
      _o3->setup() ;
      _o2->setup() ;
      _o1->setup() ;
      _o0->setup() ;  
    }
    
    void operator=(byte op){
      _o3->write((op >> 3) & 1) ;
      _o2->write((op >> 2) & 1) ;
      _o1->write((op >> 1) & 1) ;
      _o0->write((op >> 0) & 1) ;
    }
} ;


#endif
