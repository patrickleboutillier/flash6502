#ifndef VECTORS_H
#define VECTORS_H


class VECTORS {
  private:
    uint8_t _resetl, _reseth ;
    uint8_t _intl, _inth ;
    uint8_t _nmil, _nmih ;
 
  public:
    VECTORS(){
        _resetl = 0 ;
        _reseth = 0 ;
        _intl = 0 ;
        _inth = 0 ;
        _nmil = 0 ;
        _nmih = 0 ;
    }

    void set_reset(uint16_t addr){
        _resetl = addr & 0xFF ;
        _reseth = addr >> 8 ;
    }

    void set_int(uint16_t addr){
        _intl = addr & 0xFF ;
        _inth = addr >> 8 ;
    }

    void set_nmi(uint16_t addr){
        _nmil = addr & 0xFF ;
        _nmih = addr >> 8 ;
    }

    // Not the real address here, just the lower 4 bits.
    uint8_t get_byte(uint8_t addr){
        switch (addr){
            case 0xF: return _inth ;
            case 0xE: return _intl ;
            case 0xD: return _reseth ;
            case 0xC: return _resetl ;
            case 0xB: return _nmih ;
            case 0xA: return _nmil ;
        }
        
        return 0 ;
    }

    // Not the real address here, just the lower 4 bits.
    void set_byte(uint8_t addr, uint8_t data){
        switch (addr){
            case 0xF: _inth = data ; return ;
            case 0xE: _intl = data ; return ;
            case 0xD: _reseth = data ; return ;
            case 0xC: _resetl = data ; return ;
            case 0xB: _nmih = data ; return ;
            case 0xA: _nmil = data ; return ;
        }
    }
} ;


#endif
