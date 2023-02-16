uint8_t fetch(uint8_t step) { // 1 cycle
    if ((INST == INST_RST1)||(INST == INST_RST2)||(INST == INST_MON)){
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)

        switch (step){
            case NEXT:  INST_done = 0 ; break ;  // it's important that nothing else happens here
            default:    return 0 ;
        }
    }
    else if ((INST == INST_IRQ)||(INST == INST_NMI)){
        // Interrupt (IRQ or NMI). The controller has already setup INST, so there is nothing else to do.
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
        
        switch (step){
            case NEXT:  INST_done = 0 ; break ;  // it's important that nothing else happens here
            case NEXT:  EAl_s.toggle() ; break ; // INST is also on the data bus at this point,
            case NEXT:  EAl_s.toggle() ; break ; //   store it in EAl
            default:    return 0 ;
        }
    }
    else {
        switch (step){
            enum { COUNTER_BASE = __COUNTER__ } ;
            #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
            case NEXT:  INST_done = 0 ; break ;   // it's important that nothing else happens here
            case NEXT:  PC_e.toggle() ; RAM_e.toggle() ; 
                        INST_s.toggle() ; 
                        break ;
            case NEXT:  INST_s.toggle() ; PC_up.toggle() ; break ;
            case NEXT:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t imp(uint8_t step) { //implied
    switch (step){
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t acc(uint8_t step) { // 1 cycle
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        case NEXT:  ACC_e.toggle() ;
                    A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  ACC_e.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t imm(uint8_t step) { // 1 cycle
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        case NEXT:  PC_e.toggle() ; Ah2D_e.toggle() ;
                    EAh_s.toggle() ; break ;
        case NEXT:  EAh_s.toggle() ; break ;
        case NEXT:  Ah2D_e.toggle() ; PC_e.toggle() ; break ;

        case NEXT:  PC_e.toggle() ; Al2D_e.toggle() ;
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; PC_e.toggle() ; break ;

        case NEXT:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ;
                    A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; B_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; PC_up.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t zp(uint8_t step) { // 3 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        case NEXT:  EAh_s.toggle() ; break ;
        case NEXT:  EAh_s.toggle() ; break ;

        case NEXT:  PC_e.toggle() ; RAM_e.toggle() ;
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  PC_e.toggle() ; break ;

        case NEXT:  EAl_e.toggle() ;
                    A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; B_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpx(uint8_t step) { // 5 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        case NEXT:  EAh_s.toggle() ; break ; 
        case NEXT:  EAh_s.toggle() ; break ;

        case NEXT:  X_e.toggle() ; 
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  X_e.toggle() ; break ;
    
        case NEXT:  PC_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; PC_e.toggle() ; break ;
    
        case NEXT:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
    
        case NEXT:  EAl_e.toggle() ; RAM_e.toggle() ;  
                    A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; B_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpy(uint8_t step) { // 5 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        case NEXT:  EAh_s.toggle() ; break ; 
        case NEXT:  EAh_s.toggle() ; break ;

        case NEXT:  Y_e.toggle() ;  
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  Y_e.toggle() ; break ;
    
        case NEXT:  PC_e.toggle() ; RAM_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; PC_e.toggle() ; break ;
    
        case NEXT:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
    
        case NEXT:  EAl_e.toggle() ; RAM_e.toggle() ; 
                    A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; B_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t rel(uint8_t step){ // 7 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        case NEXT:  PC_e.toggle() ; RAM_e.toggle() ; 
                    A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; B_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;

        case NEXT:  ALU_op = ALU_SXT ; 
                    ALU_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case NEXT:  EAh_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
    
        case NEXT:  PC_e.toggle() ; Al2D_e.toggle() ; 
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; PC_e.toggle() ; break ;
    
        case NEXT:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; 
                    EAl_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
    
        case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ; 
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
    
        case NEXT:  PC_e.toggle() ; Ah2D_e.toggle() ; 
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Ah2D_e.toggle() ; PC_e.toggle() ; break ;
    
        case NEXT:  ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case NEXT:  EAh_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t abso(uint8_t step) { // 3 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch(step) {
        case NEXT:  PC_e.toggle() ; RAM_e.toggle() ; 
                    EAl_s.toggle() ; break ; 
        case NEXT:  EAl_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  PC_up.toggle() ;
         
                    EAh_s.toggle() ; break ;
        case NEXT:  EAh_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  PC_e.toggle() ; PC_up.toggle() ; break ;

        case NEXT:  EAh_e.toggle() ; EAl_e.toggle() ; 
                    A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absx(uint8_t step) { // 7 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch(step) {
        case NEXT:  X_e.toggle() ;
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  X_e.toggle() ; break ;
        
        case NEXT:  PC_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; 
                    EAl_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;

        case NEXT:  PC_e.toggle() ; RAM_e.toggle() ;  
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case NEXT:  EAh_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
        
        case NEXT:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; 
                    A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absy(uint8_t step) { // 7 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch(step) {
        case NEXT:  Y_e.toggle() ; 
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  Y_e.toggle() ; break ;
        
        case NEXT:  PC_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; 
                    EAl_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;

        case NEXT:  PC_e.toggle() ; RAM_e.toggle() ;  
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case NEXT:  EAh_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
        
        case NEXT:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; 
                    A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t ind(uint8_t step) { // 8 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch(step) {
        case NEXT:  PC_e.toggle() ; RAM_e.toggle() ; 
                    EAl_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; EAl_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  PC_up.toggle() ; 
        
                    EAh_s.toggle() ; break ;
        case NEXT:  EAh_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case NEXT:  EAh_e.toggle() ; EAl_e.toggle() ; 
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
        
        case NEXT:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case NEXT:  EAh_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
        
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ; 

        case NEXT:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indx(uint8_t step) { // 10 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch(step) {
        case NEXT:  PC_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case NEXT:  X_e.toggle() ; 
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  X_e.toggle() ; break ;

        case NEXT:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ; 
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

        case NEXT:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case NEXT:  EAl_e.toggle() ; RAM_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case NEXT:  EAh_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case NEXT:  EAl_e.toggle() ; RAM_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case NEXT:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; 
                    A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indy(uint8_t step) { // 10 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch(step) {
        case NEXT:  PC_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case NEXT:  Y_e.toggle() ; 
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  Y_e.toggle() ; break ;

        case NEXT:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case NEXT:  EAl_e.toggle() ; RAM_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case NEXT:  EAh_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; break ;

        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ; 
        
        case NEXT:  EAl_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; 
                    EAl_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        
        case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ; 
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;

        case NEXT:  ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case NEXT:  EAh_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case NEXT:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; 
                    A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; B_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}