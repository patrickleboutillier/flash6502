#ifndef SENSOR_H
#define SENSOR_H


#include <vector>
#include "signal.h"


class sensor {
    public:
        void add_signal(signal *s){
            s->connect(this) ;
        }

        
        virtual void always() = 0 ;
} ;


#endif
