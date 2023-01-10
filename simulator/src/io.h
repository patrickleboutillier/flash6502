class IO {
  public:
    IO(){
    }

    // Not the real address here, just the lower 4 bits.
    uint8_t get_byte(uint8_t addr){
        switch (addr){
            case 0x0: {
              uint8_t b = 0 ;
              int rc = read(0, &b, 1) ;
              //printf("[%c]\n", b) ;
              if (rc == -1){
                if (errno != EAGAIN){
                  fprintf(stderr, "read error\n") ;
                  exit(1) ;
                }
              }
              return b ; // stdin
            }
        }
        
        return 0 ;
    }

    // Not the real address here, just the lower 4 bits.
    void set_byte(uint8_t addr, uint8_t data){
        switch (addr){
            case 0x0: // stdin
              return ;
            case 0x1: // stdout 
              write(1, &data, 1) ;
              return ;
            case 0x2: // stderr
              write(2, &data, 1) ;
              return ;
            case 0x9: // halt
              fprintf(stderr, "HALTED!\n") ;
              exit(0) ;
              return ;
        }
    }
} ;