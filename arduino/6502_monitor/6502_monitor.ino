#include "DATA.h"
#include "VECTORS.h"
bool HALTED = false ;
#include "IO.h"
#include "CTRL.h"
#include "PROG.h"
#include "TEST.h"

// Push button  
#define NMI   A5
#define IRQ   A4
#define STEP  NMI      
#define MON   IRQ   

DATA DATA ;              // 9, 8, 7, 6, 5, 4, 3, 2
VECTORS VECTORS ;
IO IO ;
CTRL CTRL(&DATA, &VECTORS, &IO) ;      // 12, 11, 10, A1


bool PROGRESS = false ;

#include "fake6502.h"


void setup() {
  // Faster analog reads
  ADCSRA = (ADCSRA & 0b11111000) | 0b100 ;

  Serial.begin(9600) ;
  Serial.setTimeout(1000) ;
  // Send null byte to indicate we have finished booting, in case a loader is present.
  Serial.write(0) ;
  Serial.println(F("Starting Flash6502")) ;  

  PROG *prog = detect_loader() ;

  if (! digitalRead(MON)){
    Serial.println(F("IRQ/MON button held down, entering monitor mode.\n")) ;
    DEBUG_MON = true ;
  }
  if (! digitalRead(STEP)){
    Serial.println(F("NMI/STEP button held down, entering step mode.\n")) ;
    DEBUG_STEP = true ;
    DEBUG_MON = true ;
  }
  
  reset6502(prog) ;
}


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

  PROGRESS = true ;
  
  return new PROG("TestSuite", test_suite, 14649, true, 0x0400, 0x38A7, 0x3899, 0x3699) ;
  //return new PROG("Hello", hello, 0x0021, false, 0x0010, 0x0020, 0x0020) ;
}
