#ifndef INPUT_H
#define INPUT_H


#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "component.h"

template <uint32_t W> class output ;


template <uint32_t W> class input {
    private:
        component *_component ;
    public:
        output<W> *_driver ;

        input(){
            _component = nullptr ;
            _driver = nullptr ;
        } ;

        input(component* c) : input(){
            _component = c ;
        } ;

        uint32_t get_value(){
            assert(_driver != nullptr) ;
            return _driver->get_value() ;
        } ;

        void operator=(input<W> i){
            assert(i._driver != nullptr) ;
            _driver = i._driver ;
            always() ;
        }

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