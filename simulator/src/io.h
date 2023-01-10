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
              fprintf(stderr, "read error: %s\n", strerror(errno)) ;
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
        case 0x1: { // stdout 
          int nb = write(1, &data, 1) ;
          if (nb < 1){
            fprintf(stderr, "write error: %s\n", strerror(errno)) ;
            exit(1) ;
          }
          return ;
        }
        case 0x2: { // stderr
          int nb = write(2, &data, 1) ;
          if (nb < 1){
            fprintf(stderr, "write error: %s\n", strerror(errno)) ;
            exit(1) ;
          }
          return ;
        }
        case 0x9: // halt
          fprintf(stderr, "HALTED!\n") ;
          exit(0) ;
            return ;
      }
    }
} ;