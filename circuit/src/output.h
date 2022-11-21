#ifndef OUTPUT_H
#define OUTPUT_H


#include <unordered_set>
#include <stdint.h>
#include <assert.h>
#include "input.h"
#include "component.h"

using namespace std ;


template <uint32_t W> class output {
    private:
        uint32_t _value ;
        uint32_t _mask ;
        bool _set ;
        unordered_set<input<W> *> _connected_inputs ;
    public:
        bool _drive ;
        
        output(uint32_t v = 0){
            _set = false ;
            _value = v ;
            _mask = (1 << W) - 1 ;
            _drive = true ;
        }

        output(const char *name, uint32_t v = 0) : output(v) {
        } 

        void set_value(uint32_t v){
            if ((v != _value)||(! _set)){ 
                _value = v & _mask ;
                _set = true ;
                if (_drive){
                    // Iterate through all the connected_inputs and call always()
                    typename unordered_set<input<W> *>::iterator i ;
                    for (i = _connected_inputs.begin(); i != _connected_inputs.end() ; i++){
                        (*i)->always() ;
                    }
                }
            }
        }

        // Really only makes sense for output<1>...
        void toggle(){
            set_value(~ _value) ;
        }

        void operator=(uint32_t v){
            set_value(v) ;
        }

        void operator=(output<W> o){
            set_value(o.get_value()) ;
        }

        void set_value(input<W> &i){
            set_value(i.get_value()) ;
        } 

        uint32_t get_value(){
            return _value ;
        }

        operator uint32_t(){
            return get_value() ;
        }

        void connect(input<W> &i){
            _connected_inputs.insert(&i) ;
            if (_drive){
                i._driver = this ;          
            }
        }

        void disconnect(input<W> &i){
            _connected_inputs.erase(&i) ;
            if (i._driver == this){
                i._driver = nullptr ;
            }
        }

        void drive(bool d){
            if (! d){
                // Simulate pull down resistor...
                set_value(0) ;
            }

            _drive = d ;

            typename unordered_set<input<W> *>::iterator i ;
            for (i = _connected_inputs.begin(); i != _connected_inputs.end() ; i++){
                if (_drive){
                    if ((*i)->_driver != this){
                        assert((*i)->_driver == nullptr) ;
                        (*i)->_driver = this ;
                        (*i)->always() ;
                    }
                }
                else {
                    if ((*i)->_driver == this){
                        (*i)->_driver = nullptr ;
                    }
                }
            }
        }
} ;


#endif