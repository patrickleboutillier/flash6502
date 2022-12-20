#include "PROG.h"

PROG progTestSuite("progTestSuite", &E1, 14649, 0x0400, 0x38A7, 0x3899, 0x3699) ;


const uint8_t bytes42[] = {
  0x18,
  0xA9,
  0x14,
  0x69,
  0x16,
  0xDB
} ;
PROG prog42("prog42", bytes42, sizeof(bytes42)) ;


PROGMEM const uint8_t bytesHello[] = {
  /* PC:0x0000 */  0x4C,  0x13,  0x00,  0x48,  0x65,  0x6C,  0x6C,  0x6F,  0x20,  0x57,  0x6F,  0x72,  0x6C,  0x64,  0x21,  0x0A,
  /* PC:0x0010 */  0x00,  0x03,  0x00,  0xA0,  0x00,  0xB1,  0x11,  0xF0,  0x07,  0x8D,  0xF1,  0xFF,  0xC8,  0x4C,  0x15,  0x00,
  /* PC:0x0020 */  0x4C,  0x20,  0x00
} ;
PROG progHello("progHello", bytesHello, sizeof(bytesHello), true, 0x0000, 0, 0, 0x0020) ;


PROGMEM const uint8_t bytesStar[] = {
  /* PC:0x0000 */  0x2A,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x2A,  0x0A,  0x20,  0x20,  0x20,  0x20,  0x2A,  0x2A,
  /* PC:0x0010 */  0x20,  0x20,  0x20,  0x20,  0x20,  0x2A,  0x2A,  0x0A,  0x20,  0x20,  0x20,  0x20,  0x2A,  0x2A,  0x2A,  0x20,
  /* PC:0x0020 */  0x20,  0x20,  0x2A,  0x2A,  0x2A,  0x0A,  0x20,  0x20,  0x20,  0x20,  0x2A,  0x2A,  0x2A,  0x2A,  0x20,  0x2A,
  /* PC:0x0030 */  0x2A,  0x2A,  0x2A,  0x0A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,
  /* PC:0x0040 */  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x0A,  0x20,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,
  /* PC:0x0050 */  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x0A,  0x20,  0x20,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,
  /* PC:0x0060 */  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x0A,  0x20,  0x20,  0x20,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,
  /* PC:0x0070 */  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x0A,  0x20,  0x20,  0x20,  0x20,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,
  /* PC:0x0080 */  0x2A,  0x2A,  0x2A,  0x0A,  0x20,  0x20,  0x20,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,
  /* PC:0x0090 */  0x2A,  0x2A,  0x0A,  0x20,  0x20,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,
  /* PC:0x00A0 */  0x2A,  0x2A,  0x0A,  0x20,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,
  /* PC:0x00B0 */  0x2A,  0x2A,  0x2A,  0x0A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,
  /* PC:0x00C0 */  0x2A,  0x2A,  0x2A,  0x2A,  0x2A,  0x0A,  0x20,  0x20,  0x20,  0x20,  0x2A,  0x2A,  0x2A,  0x2A,  0x20,  0x2A,
  /* PC:0x00D0 */  0x2A,  0x2A,  0x2A,  0x0A,  0x20,  0x20,  0x20,  0x20,  0x2A,  0x2A,  0x2A,  0x20,  0x20,  0x20,  0x2A,  0x2A,
  /* PC:0x00E0 */  0x2A,  0x0A,  0x20,  0x20,  0x20,  0x20,  0x2A,  0x2A,  0x20,  0x20,  0x20,  0x20,  0x20,  0x2A,  0x2A,  0x0A,
  /* PC:0x00F0 */  0x20,  0x20,  0x20,  0x20,  0x2A,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x2A,  0x0A,  0x00,  0x00,
  /* PC:0x0100 */  0xA9,  0x20,  0x8D,  0xF1,  0xFF,  0x8D,  0xF1,  0xFF,  0x8D,  0xF1,  0xFF,  0x8D,  0xF1,  0xFF,  0xA0,  0x00,
  /* PC:0x0110 */  0xB1,  0xFE,  0xF0,  0x03,  0x8D,  0xF1,  0xFF,  0xC8,  0xD0,  0xF6,  0x4C,  0x1A,  0x01
} ;
PROG progStar("progStar", bytesStar, sizeof(bytesStar), true, 0x0100, 0, 0, 0x011A) ;
