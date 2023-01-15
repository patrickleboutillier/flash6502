// A program definition in a stream of bytes

class PROG {
  private:
    const char *_name ;
    const uint8_t *_bytes ;
    uint32_t _len ;
    uint32_t _pc ;
    uint16_t _start_addr ;
    uint16_t _int_addr ;
    uint16_t _nmi_addr ;
    uint16_t _done_addr ;

  public:
    // Program that is defined in a file
    PROG(const char *name, const char *file, uint16_t start_addr = 0, uint16_t int_addr = 0, uint16_t nmi_addr = 0, uint16_t done_addr = 0){
        _pc = 0 ;
        _name = name ;
        _start_addr = start_addr ;
        _int_addr = int_addr ;
        _nmi_addr = nmi_addr ;
        _done_addr = done_addr ;

        // Load the program from the file
        FILE *f = fopen(file, "rb") ;
        uint8_t *bytes = (uint8_t *)malloc(0x10000 * sizeof(uint8_t)) ;
        _len = fread(bytes, 1, 0x10000, f) ;
        fclose(f) ;
        
        _bytes = bytes ;
    }

    const char *name(){
        return _name ;
    }

    uint32_t len(){
        return _len ;
    }

    int get_next_byte(){
        if (_pc >= _len){
            return -1 ;
        }

        uint8_t data = _bytes[_pc] ;
        switch (_pc){
            case 0xFFFA: _nmi_addr = data ; break ;
            case 0XFFFB: _nmi_addr |= data << 8 ; break ;
            case 0xFFFC: _start_addr = data ; break ;
            case 0XFFFD: _start_addr |= data << 8 ; break ;
            case 0xFFFE: _int_addr = data ; break ;
            case 0XFFFF: _int_addr |= data << 8 ; break ;
        }

        _pc++ ;

        return data ;
    }

    uint16_t start_addr(){
        return _start_addr ;
    }

    uint16_t int_addr(){
        return _int_addr ;
    }

    uint16_t nmi_addr(){
        return _nmi_addr ;
    }
    
    uint16_t done_addr(){
        return _done_addr ;
    }

    bool is_done(uint16_t pc){
        return (_done_addr != 0 ? pc == _done_addr : false) ;
    }

    void describe(){
        printf("\nProgram to run is '%s':\n", _name) ;
        printf("- It has %d instructions\n", _len) ;
        printf("- Reset vector is 0x%04X\n", _start_addr) ;
        printf("- Interrupt vector is 0x%04X\n", _int_addr) ;
        printf("- Non-maskable interrupt vector is 0x%04X\n", _nmi_addr) ;
        if (_done_addr){
            printf("- It will be considered done when PC reaches 0x%04X\n", _done_addr) ;
        }
    }
} ;