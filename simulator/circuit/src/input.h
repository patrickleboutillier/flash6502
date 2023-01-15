#ifndef INPUT_H
#define INPUT_H

#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "component.h"

using namespace std ;

template <uint32_t W> class output ;

#define ALLOW_MULTIPLE_DRIVERS  true


template <uint32_t W> class input {
    private:
        component *_component ;
        vector<output<W> *> _drivers ;
        
    public:
        input(){
            _component = nullptr ;
        } ;

        input(component* c) : input(){
            _component = c ;
        } ;

        bool driven(){
            return ! _drivers.empty() ;
        }

        int nb_drivers(){
            return _drivers.size() ;
        }

        void add_driver(output<W> *d){
            if (find(_drivers.begin(), _drivers.end(), d) == _drivers.end()) {
                _drivers.push_back(d) ;
            }
        }

        void remove_driver(output<W> *d){
            _drivers.erase(remove(_drivers.begin(), _drivers.end(), d), _drivers.end()) ;
        }

        output<W> *get_driver(){
            if (! driven()){
                return nullptr ;
            }

            #if !ALLOW_MULTIPLE_DRIVERS
                assert(_drivers.size() == 1) ;
            #endif
            // Return last registered driver
            return _drivers.back() ;
        }

        uint32_t get_value(){
            if (driven()){
                return get_driver()->get_value() ;
            }
            else {
                // Simulate pull down resistor
                return 0 ;
            }
        } ;

        operator uint32_t(){
            return get_value() ;
        }

        void always(){
            if (_component != nullptr){
                _component->always(this) ;
            }
        }
} ;


#endif