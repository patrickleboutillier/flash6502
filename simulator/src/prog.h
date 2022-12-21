class PROG {
  private:
    const char *_name ;
    const uint8_t *_bytes ;
    uint32_t _len ;
    uint16_t _start_addr ;
    uint16_t _int_addr ;
    uint16_t _nmi_addr ;
    uint16_t _done_addr ;

  public:
    // Program that is defined in the simulator RAM
    PROG(const char *name, const uint8_t *bytes, uint16_t len, uint16_t start_addr = 0, uint16_t int_addr = 0, uint16_t nmi_addr = 0, uint16_t done_addr = 0){
        _name = name ;
        _bytes = bytes ;
        _len = len ;
        _start_addr = start_addr ;
        _int_addr = int_addr ;
        _nmi_addr = nmi_addr ;
        _done_addr = done_addr ;
    }

    // Program that is defined in a file
    PROG(const char *name, const char *file, uint16_t start_addr = 0, uint16_t int_addr = 0, uint16_t nmi_addr = 0, uint16_t done_addr = 0){
        _name = name ;

        // Load the program from the file
        FILE *f = fopen(file, "rb") ; 
        uint8_t *bytes = (uint8_t *)malloc(0x10000 * sizeof(uint8_t)) ;
        _len = fread(bytes, 1, 0x10000, f) ;
        fclose(f) ;
        
        _bytes = bytes ;
        if ((_len >= 0xFFFC)&&(! start_addr)){
            _start_addr = _bytes[0xFFFD] << 8 | _bytes[0xFFFC] ;
        }
        else {
            _start_addr = start_addr ;
        }
        _int_addr = (_len >= 0xFFFE ? (_bytes[0xFFFF] << 8 | _bytes[0xFFFE]) : int_addr) ;
        _nmi_addr = (_len >= 0xFFFA ? (_bytes[0xFFFB] << 8 | _bytes[0xFFFA]) : nmi_addr) ;
        _done_addr = done_addr ;
    }

    const char *name(){
        return _name ;
    }

    uint32_t len(){
        return _len ;
    }

    uint8_t get_byte(uint16_t addr){
        if (addr < _len){
            return _bytes[addr] ;
        }
        
        return 0 ;
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