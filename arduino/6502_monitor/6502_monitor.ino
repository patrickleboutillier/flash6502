#include "DATA.h"
#include "CTRLSIG.h"
#include "CTRL_OUT.h"
#include "VECTORS.h"
#include "TEST.h"

#define SERIAL_TIMEOUT 1000
bool HALTED = false ;
#include "IO.h"
#include "PROG.h"


// Push button  
#define NMI   A5
#define IRQ   A4
#define STEP  NMI      
#define MON   IRQ   

#define CTRL A2         // Activate controller for vectors and IO
#define CTRL_ADDR0 A2
#define CTRL_ADDR1 A3
#define CTRL_ADDR2 A6
#define CTRL_ADDR3 A7

DATA DATA ;              // 9, 8, 7, 6, 5, 4, 3, 2
CTRLSIG CTRL_src(NULL, 13) ;
CTRL_OUT CTRL_OUT ;      // 12, 11, 10, A1
VECTORS VECTORS ;
IO IO ;

// Program to run
PROG *prog = NULL ;


#include "fake6502.h"

  
void setup() {
  // Faster analog reads
  ADCSRA = (ADCSRA & 0b11111000) | 0b100 ;

  Serial.begin(9600) ;
  Serial.setTimeout(SERIAL_TIMEOUT) ;
  // Send null byte to indicate we have finished booting, in case a loader is present.
  Serial.write(0) ;
  Serial.println(F("Starting Flash6502")) ;  
  prog = detect_loader() ;

  CTRL_src.setup() ;

  if (! digitalRead(MON)){
    Serial.println(F("IRQ/MON button held down, entering monitor mode.\n")) ;
    DEBUG_MON = true ;
  }
  if (! digitalRead(STEP)){
    Serial.println(F("NMI/STEP button held down, entering step mode.\n")) ;
    DEBUG_STEP = true ;
    DEBUG_MON = true ;
  }
  
  reset6502(prog /*, 0x2014*/) ;
}


const uint8_t hello[] = {
  /* PC:0x0000 */  0x48,  0x65,  0x6C,  0x6C,  0x6F,  0x20,  0x57,  0x6F,  0x72,  0x6C,  0x64,  0x21,  0x0A,  0x00,  0x00,  0x00,
  /* PC:0x0010 */  0xA0,  0x00,  0xB1,  0x0E,  0xF0,  0x07,  0x8D,  0xF1,  0xFF,  0xC8,  0x4C,  0x12,  0x00,  0x8D,  0xF9,  0xFF,
  /* PC:0x0020 */  0x40
} ;


PROG *detect_loader(){
  // Read the magic numer that indicates our loader is present.
  byte magic[3] ;
  int nb = Serial.readBytes(magic, 3) ;
  if ((magic[0] == 0x65)&&(magic[1] == 0x02)){
    IO.set_loader() ;
    if (magic[2] == 0xFF){
      MON_EVERY = 0 ;
      Serial.println(F("Loader detected, program will be requested from loader.")) ;
      return new PROG("@loader") ;
    }
    else {
      Serial.println(F("Loader detected, continuing with built-in test suite.")) ;
    }
  }
  else {
    Serial.println(F("No loader detected, continuing with built-in test suite.")) ;
  }

  return new PROG("TestSuite", test_suite, 14649, true, 0x0400, 0x38A7, 0x3899, 0x3699) ;
  //return new PROG("Hello", hello, 0x0021, false, 0x0010, 0x0020, 0x0020) ;
}
