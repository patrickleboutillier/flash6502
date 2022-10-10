#ifndef ROM_H
#define ROM_H

#include "hdl/bus.h"
#include "hdl/buf.h"
#include "hdl/sensor.h" 


class ROM : public sensor {
    public:
        bus addr ;
        bus data ;

        ROM() : addr(18, 0), data(8, 0) {
            add_signal(&addr) ;
        }
} ;


#endif