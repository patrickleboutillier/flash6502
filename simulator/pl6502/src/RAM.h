#ifndef RAM_H
#define RAM_H


#include "circuit.h"


class RAM : public component {
    public:
        input<8> data_in, addrh, addrl ;
        input<1> set, enable ;
        output<8> data_out ;
        output<1> ctrl ;
    private:
        uint8_t _mem[256][256] ;

    public:
        RAM() : data_in(this), addrh(this), addrl(this), set(this), enable(this) {
            data_out.drive(false) ;

            // Fill RAM with random values
            for (int i = 0 ; i < 256 ; i++){
                for (int j = 0 ; j < 256 ; j++){
                    _mem[i][j] = rand() & 0xFF ;
                }
            }
        } ;


        uint8_t peek(uint16_t addr){
            return _mem[addr >> 8][addr & 0xFF] ;
        }


        void always(const void *trigger){
            // RAM is limited to the range 0x0000 => 0xF7FF, the rest of the address space is assigned to the controller.
            // This means that the controller handles the vectors in the range 0xFFFA => 0xFFFF
            if ((addrh & 0xF8) == 0xF8){
                // Stop driving bus in case we were still driving it.
                data_out.drive(false) ;
                ctrl = 1 ;
                return ;
            }
            else {
                ctrl = 0 ;
            }

            if (! set){ // negative logic
                //printf("write %02X%02X\n", (uint8_t)addrh, (uint8_t)addrl) ;
                _mem[addrh][addrl] = data_in ;
            }
            else if (trigger == &data_in){
                // Ignore changes on the data bus or address busses if set is not active.
                return ;
            }

            if (! enable){ // negative logic
                //printf("read %02X%02X\n", (uint8_t)addrh, (uint8_t)addrl) ;
                // Here we use a soft drive here since there are sometimes race conditions with the controller
                // The controller can drive the bridge a bit longer (see process_ctrl()) after an address change
                // (from the controller range to the RAM range) and the RAM_e signal has not been turned off yet,
                // the RAM will try to drive the bus while the controller is still on it...
                data_out.drive(true) ;
                data_out = _mem[addrh][addrl] ;
            }
            else {
                data_out.drive(false) ;
            }
        } ;
} ;


#endif