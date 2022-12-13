#include "PROG.h"

uint8_t bytes42[] = {
  0x18,
  0xA9,
  0x14,
  0x69,
  0x16,
  0xDB
} ;
PROG prog42("prog42", bytes42, sizeof(bytes42)) ;


PROG progTestSuite("progTestSuite", &E1, 14625) ;
