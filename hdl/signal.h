#ifndef SIGNAL_H
#define SIGNAL_H


#include <vector>
class sensor ;


class signal {
    protected:
        std::vector<std::pair<sensor *,uint16_t>> _sensors ;

    public:
        virtual void connect(sensor *s){
            _sensors.push_back(std::make_pair(s, 0)) ;
        }


        void connect(sensor *s, uint16_t filter){
            _sensors.push_back(std::make_pair(s, filter)) ;
        }
} ;


#endif
